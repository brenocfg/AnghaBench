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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 void* GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  deobfuscate_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

void *get_obfuscated_func(HMODULE module, const char *str, uint64_t val)
{
	char new_name[128];
	strcpy(new_name, str);
	deobfuscate_str(new_name, val);
	return GetProcAddress(module, new_name);
}