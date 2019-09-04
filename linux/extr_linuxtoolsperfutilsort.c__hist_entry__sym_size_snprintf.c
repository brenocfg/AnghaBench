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
struct symbol {int dummy; } ;

/* Variables and functions */
 int repsep_snprintf (char*,size_t,char*,unsigned int,char*) ; 
 char* symbol__size (struct symbol*) ; 

__attribute__((used)) static int _hist_entry__sym_size_snprintf(struct symbol *sym, char *bf,
					  size_t bf_size, unsigned int width)
{
	if (sym)
		return repsep_snprintf(bf, bf_size, "%*d", width, symbol__size(sym));

	return repsep_snprintf(bf, bf_size, "%*s", width, "unknown");
}