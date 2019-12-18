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

/* Variables and functions */
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,char const*,char const*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static void del_mapping_key(const WCHAR *device, const WCHAR *username, const WCHAR *guid) {
    static const WCHAR subkey[] = {
        'S','o','f','t','w','a','r','e','\\',
        'W','i','n','e','\\',
        'D','i','r','e','c','t','I','n','p','u','t','\\',
        'M','a','p','p','i','n','g','s','\\','%','s','\\','%','s','\\','%','s','\0'};
    WCHAR *keyname;

    keyname = heap_alloc(sizeof(WCHAR) * (lstrlenW(subkey) + strlenW(username) + strlenW(device) + strlenW(guid)));
    sprintfW(keyname, subkey, username, device, guid);

    /* Remove old key mappings so there will be no overlapping mappings */
    RegDeleteKeyW(HKEY_CURRENT_USER, keyname);

    heap_free(keyname);
}