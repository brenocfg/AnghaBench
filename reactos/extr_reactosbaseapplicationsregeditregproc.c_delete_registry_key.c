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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 char* GetMultiByteString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SHDeleteKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getAppName () ; 
 int /*<<< orphan*/  parseKeyName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 

void delete_registry_key(WCHAR *reg_key_name)
{
    WCHAR *key_name = NULL;
    HKEY key_class;

    if (!reg_key_name || !reg_key_name[0])
        return;

    if (!parseKeyName(reg_key_name, &key_class, &key_name)) {
        char* reg_key_nameA = GetMultiByteString(reg_key_name);
        fprintf(stderr,"%S: Incorrect registry class specification in '%s'\n",
                getAppName(), reg_key_nameA);
        HeapFree(GetProcessHeap(), 0, reg_key_nameA);
        exit(1);
    }
    if (!*key_name) {
        char* reg_key_nameA = GetMultiByteString(reg_key_name);
        fprintf(stderr,"%S: Can't delete registry class '%s'\n",
                getAppName(), reg_key_nameA);
        HeapFree(GetProcessHeap(), 0, reg_key_nameA);
        exit(1);
    }

    SHDeleteKey(key_class, key_name);
}