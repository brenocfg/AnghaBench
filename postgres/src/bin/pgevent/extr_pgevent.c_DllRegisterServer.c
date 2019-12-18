#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  key_name ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  STDAPI ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int EVENTLOG_ERROR_TYPE ; 
 int EVENTLOG_INFORMATION_TYPE ; 
 int EVENTLOG_WARNING_TYPE ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int MB_ICONSTOP ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_EXPAND_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKey (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SELFREG_E_TYPELIB ; 
 int /*<<< orphan*/  S_OK ; 
 int _MAX_PATH ; 
 int /*<<< orphan*/  _snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_source ; 
 scalar_t__ g_module ; 
 int strlen (char*) ; 

STDAPI
DllRegisterServer(void)
{
	HKEY		key;
	DWORD		data;
	char		buffer[_MAX_PATH];
	char		key_name[400];

	/* Set the name of DLL full path name. */
	if (!GetModuleFileName((HMODULE) g_module, buffer, sizeof(buffer)))
	{
		MessageBox(NULL, "Could not retrieve DLL filename", "PostgreSQL error", MB_OK | MB_ICONSTOP);
		return SELFREG_E_TYPELIB;
	}

	/*
	 * Add PostgreSQL source name as a subkey under the Application key in the
	 * EventLog registry key.
	 */
	_snprintf(key_name, sizeof(key_name),
			  "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\%s",
			  event_source);
	if (RegCreateKey(HKEY_LOCAL_MACHINE, key_name, &key))
	{
		MessageBox(NULL, "Could not create the registry key.", "PostgreSQL error", MB_OK | MB_ICONSTOP);
		return SELFREG_E_TYPELIB;
	}

	/* Add the name to the EventMessageFile subkey. */
	if (RegSetValueEx(key,
					  "EventMessageFile",
					  0,
					  REG_EXPAND_SZ,
					  (LPBYTE) buffer,
					  strlen(buffer) + 1))
	{
		MessageBox(NULL, "Could not set the event message file.", "PostgreSQL error", MB_OK | MB_ICONSTOP);
		return SELFREG_E_TYPELIB;
	}

	/* Set the supported event types in the TypesSupported subkey. */
	data = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;

	if (RegSetValueEx(key,
					  "TypesSupported",
					  0,
					  REG_DWORD,
					  (LPBYTE) &data,
					  sizeof(DWORD)))
	{
		MessageBox(NULL, "Could not set the supported types.", "PostgreSQL error", MB_OK | MB_ICONSTOP);
		return SELFREG_E_TYPELIB;
	}

	RegCloseKey(key);
	return S_OK;
}