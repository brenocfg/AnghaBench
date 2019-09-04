#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  use_proxy ;
typedef  int /*<<< orphan*/  connection_settings ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  char WCHAR ;
struct TYPE_3__ {scalar_t__ code; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ PSHNOTIFY ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  int INT_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int GetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDC_EDIT_PAC_SCRIPT ; 
 int /*<<< orphan*/  IDC_EDIT_PROXY_PORT ; 
 int /*<<< orphan*/  IDC_EDIT_PROXY_SERVER ; 
 int /*<<< orphan*/  IDC_USE_PAC_SCRIPT ; 
 int /*<<< orphan*/  IDC_USE_PROXY_SERVER ; 
 int /*<<< orphan*/  IDC_USE_WPAD ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 scalar_t__ PSN_APPLY ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteValueW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  auto_config_url ; 
 int /*<<< orphan*/  connections ; 
 int create_connection_settings (int,char*,int,int,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  default_connection_settings ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  internet_settings ; 
 int /*<<< orphan*/  proxy_enable ; 
 int /*<<< orphan*/  proxy_server ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static INT_PTR connections_on_notify(HWND hwnd, WPARAM wparam, LPARAM lparam)
{
    connection_settings *default_connection;
    WCHAR proxy[INTERNET_MAX_URL_LENGTH];
    WCHAR pac_script[INTERNET_MAX_URL_LENGTH];
    PSHNOTIFY *psn = (PSHNOTIFY*)lparam;
    DWORD proxy_len, port_len, pac_script_len;
    DWORD use_proxy, use_pac_script, use_wpad, size;
    LRESULT res;
    HKEY hkey, con;

    if(psn->hdr.code != PSN_APPLY)
        return FALSE;

    res = RegOpenKeyW(HKEY_CURRENT_USER, internet_settings, &hkey);
    if(res)
        return FALSE;

    use_proxy = IsDlgButtonChecked(hwnd, IDC_USE_PROXY_SERVER);
    res = RegSetValueExW(hkey, proxy_enable, 0, REG_DWORD,
            (BYTE*)&use_proxy, sizeof(use_proxy));
    if(res)
    {
        RegCloseKey(hkey);
        return FALSE;
    }
    TRACE("ProxyEnable set to %x\n", use_proxy);

    proxy_len = GetDlgItemTextW(hwnd, IDC_EDIT_PROXY_SERVER, proxy, ARRAY_SIZE(proxy));
    if(proxy_len)
    {
        proxy[proxy_len++] = ':';
        port_len = GetDlgItemTextW(hwnd, IDC_EDIT_PROXY_PORT, proxy+proxy_len,
                ARRAY_SIZE(proxy)-proxy_len);
        if(!port_len)
        {
            proxy[proxy_len++] = '8';
            proxy[proxy_len++] = '0';
            proxy[proxy_len] = 0;
        }

        res = RegSetValueExW(hkey, proxy_server, 0, REG_SZ,
                (BYTE*)proxy, (proxy_len+port_len)*sizeof(WCHAR));
    }
    else
    {
        res = RegDeleteValueW(hkey, proxy_server);
        if(res == ERROR_FILE_NOT_FOUND)
            res = ERROR_SUCCESS;
    }
    if(res)
    {
        RegCloseKey(hkey);
        return FALSE;
    }
    TRACE("ProxtServer set to %s\n", wine_dbgstr_w(proxy));

    use_pac_script = IsDlgButtonChecked(hwnd, IDC_USE_PAC_SCRIPT);
    pac_script_len = GetDlgItemTextW(hwnd, IDC_EDIT_PAC_SCRIPT,
            pac_script, ARRAY_SIZE(pac_script));
    if(!pac_script_len) use_pac_script = FALSE;
    if(use_pac_script)
    {
        res = RegSetValueExW(hkey, auto_config_url, 0, REG_SZ,
                (BYTE*)pac_script, pac_script_len*sizeof(WCHAR));
    }
    else
    {
        res = RegDeleteValueW(hkey, auto_config_url);
        if(res == ERROR_FILE_NOT_FOUND)
            res = ERROR_SUCCESS;
    }
    if(res)
    {
        RegCloseKey(hkey);
        return FALSE;
    }
    TRACE("AutoConfigURL set to %s\n", wine_dbgstr_w(use_pac_script ? pac_script : NULL));

    use_wpad = IsDlgButtonChecked(hwnd, IDC_USE_WPAD);

    res = RegCreateKeyExW(hkey, connections, 0, NULL, 0, KEY_WRITE, NULL, &con, NULL);
    RegCloseKey(hkey);
    if(res)
        return FALSE;

    size = create_connection_settings(use_proxy, proxy, use_wpad,
        use_pac_script, pac_script, &default_connection);
    if(!size)
    {
        RegCloseKey(con);
        return FALSE;
    }

    res = RegSetValueExW(con, default_connection_settings, 0, REG_BINARY,
            (BYTE*)default_connection, size);
    heap_free(default_connection);
    RegCloseKey(con);
    return !res;
}