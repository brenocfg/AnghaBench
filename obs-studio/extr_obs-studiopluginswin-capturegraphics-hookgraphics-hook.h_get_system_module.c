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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_path ; 

__attribute__((used)) static inline HMODULE get_system_module(const char *module)
{
	char base_path[MAX_PATH];

	strcpy(base_path, system_path);
	strcat(base_path, "\\");
	strcat(base_path, module);
	return GetModuleHandleA(base_path);
}