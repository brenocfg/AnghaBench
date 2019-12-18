#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* str; int len; } ;
typedef  TYPE_1__ strbuf ;
typedef  int /*<<< orphan*/  dw ;
typedef  char WCHAR ;
typedef  char* PBYTE ;
typedef  char* LPCOLESTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_EXCEPTION ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (scalar_t__) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegCreateKeyW (scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  RegDeleteKeyW (scalar_t__,char*) ; 
 int /*<<< orphan*/  RegDeleteTreeW (scalar_t__,char*) ; 
 scalar_t__ RegOpenKeyW (scalar_t__,char*,scalar_t__*) ; 
 scalar_t__ RegSetValueExW (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 int /*<<< orphan*/  get_word (char**,TYPE_1__*) ; 
 scalar_t__ iswspace (char) ; 
 int /*<<< orphan*/  iswxdigit (char) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char const*) ; 
 int /*<<< orphan*/  lstrlenW (char*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_write (char*,TYPE_1__*,int) ; 
 int wcstol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wcstoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT do_process_key(LPCOLESTR *pstr, HKEY parent_key, strbuf *buf, BOOL do_register)
{
    LPCOLESTR iter;
    HRESULT hres;
    LONG lres;
    HKEY hkey = 0;
    strbuf name;

    enum {
        NORMAL,
        NO_REMOVE,
        IS_VAL,
        FORCE_REMOVE,
        DO_DELETE
    } key_type = NORMAL;

    static const WCHAR wstrNoRemove[] = {'N','o','R','e','m','o','v','e',0};
    static const WCHAR wstrForceRemove[] = {'F','o','r','c','e','R','e','m','o','v','e',0};
    static const WCHAR wstrDelete[] = {'D','e','l','e','t','e',0};
    static const WCHAR wstrval[] = {'v','a','l',0};

    iter = *pstr;
    hres = get_word(&iter, buf);
    if(FAILED(hres))
        return hres;
    strbuf_init(&name);

    while(buf->str[1] || buf->str[0] != '}') {
        key_type = NORMAL;
        if(!lstrcmpiW(buf->str, wstrNoRemove))
            key_type = NO_REMOVE;
        else if(!lstrcmpiW(buf->str, wstrForceRemove))
            key_type = FORCE_REMOVE;
        else if(!lstrcmpiW(buf->str, wstrval))
            key_type = IS_VAL;
        else if(!lstrcmpiW(buf->str, wstrDelete))
            key_type = DO_DELETE;

        if(key_type != NORMAL) {
            hres = get_word(&iter, buf);
            if(FAILED(hres))
                break;
        }
        TRACE("name = %s\n", debugstr_w(buf->str));

        if(do_register) {
            if(key_type == IS_VAL) {
                hkey = parent_key;
                strbuf_write(buf->str, &name, -1);
            }else if(key_type == DO_DELETE) {
                TRACE("Deleting %s\n", debugstr_w(buf->str));
                RegDeleteTreeW(parent_key, buf->str);
            }else {
                if(key_type == FORCE_REMOVE)
                    RegDeleteTreeW(parent_key, buf->str);
                lres = RegCreateKeyW(parent_key, buf->str, &hkey);
                if(lres != ERROR_SUCCESS) {
                    WARN("Could not create(open) key: %08x\n", lres);
                    hres = HRESULT_FROM_WIN32(lres);
                    break;
                }
            }
        }else if(key_type != IS_VAL && key_type != DO_DELETE) {
            strbuf_write(buf->str, &name, -1);
            lres = RegOpenKeyW(parent_key, buf->str, &hkey);
              if(lres != ERROR_SUCCESS)
                WARN("Could not open key %s: %08x\n", debugstr_w(name.str), lres);
        }

        if(key_type != DO_DELETE && *iter == '=') {
            iter++;
            hres = get_word(&iter, buf);
            if(FAILED(hres))
                break;
            if(buf->len != 1) {
                WARN("Wrong registry type: %s\n", debugstr_w(buf->str));
                hres = DISP_E_EXCEPTION;
                break;
            }
            if(do_register) {
                switch(buf->str[0]) {
                case 's':
                    hres = get_word(&iter, buf);
                    if(FAILED(hres))
                        break;
                    lres = RegSetValueExW(hkey, name.len ? name.str :  NULL, 0, REG_SZ, (PBYTE)buf->str,
                            (lstrlenW(buf->str)+1)*sizeof(WCHAR));
                    if(lres != ERROR_SUCCESS) {
                        WARN("Could set value of key: %08x\n", lres);
                        hres = HRESULT_FROM_WIN32(lres);
                        break;
                    }
                    break;
                case 'd': {
                    DWORD dw;
                    hres = get_word(&iter, buf);
                    if(FAILED(hres))
                        break;
                    dw = wcstol(buf->str, NULL, 10);
                    lres = RegSetValueExW(hkey, name.len ? name.str :  NULL, 0, REG_DWORD,
                            (PBYTE)&dw, sizeof(dw));
                    if(lres != ERROR_SUCCESS) {
                        WARN("Could set value of key: %08x\n", lres);
                        hres = HRESULT_FROM_WIN32(lres);
                        break;
                    }
                    break;
                }
                case 'b': {
                    BYTE *bytes;
                    DWORD count;
                    DWORD i;
                    hres = get_word(&iter, buf);
                    if(FAILED(hres))
                        break;
                    count = (lstrlenW(buf->str) + 1) / 2;
                    bytes = HeapAlloc(GetProcessHeap(), 0, count);
                    if(bytes == NULL) {
                        hres = E_OUTOFMEMORY;
                        break;
                    }
                    for(i = 0; i < count && buf->str[2*i]; i++) {
                        WCHAR digits[3];
                        if(!iswxdigit(buf->str[2*i]) || !iswxdigit(buf->str[2*i + 1])) {
                            hres = E_FAIL;
                            break;
                        }
                        digits[0] = buf->str[2*i];
                        digits[1] = buf->str[2*i + 1];
                        digits[2] = 0;
                        bytes[i] = (BYTE) wcstoul(digits, NULL, 16);
                    }
                    if(SUCCEEDED(hres)) {
                        lres = RegSetValueExW(hkey, name.len ? name.str :  NULL, 0, REG_BINARY,
                            bytes, count);
                        if(lres != ERROR_SUCCESS) {
                            WARN("Could not set value of key: 0x%08x\n", lres);
                            hres = HRESULT_FROM_WIN32(lres);
                        }
                    }
                    HeapFree(GetProcessHeap(), 0, bytes);
                    break;
                }
                default:
                    WARN("Wrong resource type: %s\n", debugstr_w(buf->str));
                    hres = DISP_E_EXCEPTION;
                };
                if(FAILED(hres))
                    break;
            }else {
                if(*iter == '-')
                    iter++;
                hres = get_word(&iter, buf);
                if(FAILED(hres))
                    break;
            }
        }else if(key_type == IS_VAL) {
            WARN("value not set!\n");
            hres = DISP_E_EXCEPTION;
            break;
        }

        if(key_type != IS_VAL && key_type != DO_DELETE && *iter == '{' && iswspace(iter[1])) {
            hres = get_word(&iter, buf);
            if(FAILED(hres))
                break;
            hres = do_process_key(&iter, hkey, buf, do_register);
            if(FAILED(hres))
                break;
        }

        TRACE("%x %x\n", do_register, key_type);
        if(!do_register && (key_type == NORMAL || key_type == FORCE_REMOVE)) {
            TRACE("Deleting %s\n", debugstr_w(name.str));
            RegDeleteKeyW(parent_key, name.str);
        }

        if(hkey && key_type != IS_VAL)
            RegCloseKey(hkey);
        hkey = 0;
        name.len = 0;

        hres = get_word(&iter, buf);
        if(FAILED(hres))
            break;
    }

    HeapFree(GetProcessHeap(), 0, name.str);
    if(hkey && key_type != IS_VAL)
        RegCloseKey(hkey);
    *pstr = iter;
    return hres;
}