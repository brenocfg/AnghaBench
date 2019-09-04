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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char** registry_keys ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int OpenPhpRegistryKey(char* sub_key, HKEY *hKey)
{/*{{{*/
	const char **key_name = registry_keys;

	if (sub_key) {
		size_t main_key_len;
		size_t sub_key_len = strlen(sub_key);
		char *reg_key;

		while (*key_name) {
			LONG ret;

			main_key_len = strlen(*key_name);
			reg_key = emalloc(main_key_len + sub_key_len + 1);
			memcpy(reg_key, *key_name, main_key_len);
			memcpy(reg_key + main_key_len, sub_key, sub_key_len + 1);
			ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, reg_key, 0, KEY_READ, hKey);
			efree(reg_key);

			if (ret == ERROR_SUCCESS) {
				return 1;
			}
			++key_name;
		}
	} else {
		while (*key_name) {
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, *key_name, 0, KEY_READ, hKey) == ERROR_SUCCESS) {
				return 1;
			}
			++key_name;
		}
	}
	return 0;
}