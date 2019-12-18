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
typedef  char WCHAR ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char const*,char const*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static HKEY get_mapping_key(const WCHAR *device, const WCHAR *username, const WCHAR *guid, BOOL create)
{
    static const WCHAR subkey[] = {
        'S','o','f','t','w','a','r','e','\\',
        'W','i','n','e','\\',
        'D','i','r','e','c','t','I','n','p','u','t','\\',
        'M','a','p','p','i','n','g','s','\\','%','s','\\','%','s','\\','%','s','\0'};
    HKEY hkey;
    WCHAR *keyname;

    keyname = HeapAlloc(GetProcessHeap(), 0,
        sizeof(WCHAR) * (lstrlenW(subkey) + strlenW(username) + strlenW(device) + strlenW(guid)));
    sprintfW(keyname, subkey, username, device, guid);

    /* The key used is HKCU\Software\Wine\DirectInput\Mappings\[username]\[device]\[mapping_guid] */
    if (create) {
        if (RegCreateKeyW(HKEY_CURRENT_USER, keyname, &hkey))
            hkey = 0;
    } else if (RegOpenKeyW(HKEY_CURRENT_USER, keyname, &hkey))
            hkey = 0;

    HeapFree(GetProcessHeap(), 0, keyname);

    return hkey;
}