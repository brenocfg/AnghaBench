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
struct dso {int dummy; } ;

/* Variables and functions */
 char* demangle_sym (struct dso*,int,char const*) ; 

char *dso__demangle_sym(struct dso *dso, int kmodule, const char *elf_name)
{
	return demangle_sym(dso, kmodule, elf_name);
}