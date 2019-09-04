#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pac_url ;
typedef  int /*<<< orphan*/  enabled ;
struct TYPE_5__ {scalar_t__ version; int flags; } ;
typedef  TYPE_1__ connection_settings ;
typedef  int /*<<< orphan*/  address ;
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 scalar_t__ CONNECTION_SETTINGS_VERSION ; 
 int CONNECTION_SETTINGS_WPAD ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_LIMITTEXT ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDC_EDIT_PAC_SCRIPT ; 
 int /*<<< orphan*/  IDC_EDIT_PROXY_PORT ; 
 int /*<<< orphan*/  IDC_EDIT_PROXY_SERVER ; 
 int /*<<< orphan*/  IDC_USE_PAC_SCRIPT ; 
 int /*<<< orphan*/  IDC_USE_PROXY_SERVER ; 
 int /*<<< orphan*/  IDC_USE_WPAD ; 
 int INTERNET_MAX_URL_LENGTH ; 
 scalar_t__ REG_BINARY ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* auto_config_url ; 
 int /*<<< orphan*/  connections ; 
 scalar_t__* default_connection_settings ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 TYPE_1__* heap_realloc (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  internet_settings ; 
 scalar_t__* proxy_enable ; 
 scalar_t__* proxy_server ; 
 scalar_t__* strchrW (scalar_t__*,char) ; 
 scalar_t__ wine_dbgstr_w (scalar_t__*) ; 

__attribute__((used)) static void connections_on_initdialog(HWND hwnd)
{
    DWORD type, size, enabled;
    WCHAR address[INTERNET_MAX_URL_LENGTH], *port;
    WCHAR pac_url[INTERNET_MAX_URL_LENGTH];
    HKEY hkey, con;
    LONG res;

    SendMessageW(GetDlgItem(hwnd, IDC_EDIT_PAC_SCRIPT),
            EM_LIMITTEXT, INTERNET_MAX_URL_LENGTH, 0);
    SendMessageW(GetDlgItem(hwnd, IDC_EDIT_PROXY_SERVER),
            EM_LIMITTEXT, INTERNET_MAX_URL_LENGTH-10, 0);
    SendMessageW(GetDlgItem(hwnd, IDC_EDIT_PROXY_PORT), EM_LIMITTEXT, 8, 0);

    res = RegOpenKeyW(HKEY_CURRENT_USER, internet_settings, &hkey);
    if(res)
        return;

    size = sizeof(enabled);
    res = RegQueryValueExW(hkey, proxy_enable, NULL, &type, (BYTE*)&enabled, &size);
    if(res || type != REG_DWORD)
        enabled = 0;
    size = sizeof(address);
    res = RegQueryValueExW(hkey, proxy_server, NULL, &type, (BYTE*)address, &size);
    if(res || type != REG_SZ)
        address[0] = 0;
    size = sizeof(pac_url);
    res = RegQueryValueExW(hkey, auto_config_url, NULL, &type, (BYTE*)pac_url, &size);
    if(res || type != REG_SZ)
        pac_url[0] = 0;

    res = RegOpenKeyW(hkey, connections, &con);
    RegCloseKey(hkey);
    if(!res)
    {
        connection_settings *settings = NULL;
        size = 0;

        while((res = RegQueryValueExW(con, default_connection_settings, NULL, &type,
                        (BYTE*)settings, &size)) == ERROR_MORE_DATA || !settings)
        {
            connection_settings *new_settings = heap_realloc(settings, size);
            if(!new_settings)
            {
                RegCloseKey(con);
                heap_free(settings);
                return;
            }
            settings = new_settings;
        }
        RegCloseKey(con);

        if(!res && type == REG_BINARY)
        {
            if(settings->version != CONNECTION_SETTINGS_VERSION)
                FIXME("unexpected structure version (%x)\n", settings->version);
            else if(settings->flags & CONNECTION_SETTINGS_WPAD)
                CheckDlgButton(hwnd, IDC_USE_WPAD, BST_CHECKED);
        }
        heap_free(settings);
    }

    TRACE("ProxyEnable = %x\n", enabled);
    TRACE("ProxyServer = %s\n", wine_dbgstr_w(address));
    TRACE("AutoConfigURL = %s\n", wine_dbgstr_w(auto_config_url));

    if(enabled)
    {
        CheckDlgButton(hwnd, IDC_USE_PROXY_SERVER, BST_CHECKED);
        EnableWindow(GetDlgItem(hwnd, IDC_EDIT_PROXY_SERVER), TRUE);
        EnableWindow(GetDlgItem(hwnd, IDC_EDIT_PROXY_PORT), TRUE);
    }

    port = strchrW(address, ':');
    if(port)
    {
        *port = 0;
        port++;
    }
    SetDlgItemTextW(hwnd, IDC_EDIT_PROXY_SERVER, address);
    if(port)
        SetDlgItemTextW(hwnd, IDC_EDIT_PROXY_PORT, port);

    if(pac_url[0])
    {
        CheckDlgButton(hwnd, IDC_USE_PAC_SCRIPT, BST_CHECKED);
        EnableWindow(GetDlgItem(hwnd, IDC_EDIT_PAC_SCRIPT), TRUE);
        SetDlgItemTextW(hwnd, IDC_EDIT_PAC_SCRIPT, pac_url);
    }

    return;
}