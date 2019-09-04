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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MAXPATHLEN ; 
 scalar_t__ OpenPhpRegistryKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHPRC_REGISTRY_NAME ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (scalar_t__) ; 

char *GetIniPathFromRegistry()
{/*{{{*/
	char *reg_location = NULL;
	HKEY hKey;

	if (OpenPhpRegistryKey(NULL, &hKey)) {
		DWORD buflen = MAXPATHLEN;
		reg_location = emalloc(MAXPATHLEN+1);
		if(RegQueryValueEx(hKey, PHPRC_REGISTRY_NAME, 0, NULL, reg_location, &buflen) != ERROR_SUCCESS) {
			RegCloseKey(hKey);
			efree(reg_location);
			reg_location = NULL;
			return reg_location;
		}
		RegCloseKey(hKey);
	}
	return reg_location;
}