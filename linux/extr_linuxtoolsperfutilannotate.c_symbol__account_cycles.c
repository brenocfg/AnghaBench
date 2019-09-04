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
typedef  scalar_t__ u64 ;
struct symbol {scalar_t__ start; scalar_t__ end; } ;
struct cyc_hist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERANGE ; 
 int __symbol__account_cycles (struct cyc_hist*,scalar_t__,unsigned int,unsigned int,int) ; 
 struct cyc_hist* symbol__cycles_hist (struct symbol*) ; 

__attribute__((used)) static int symbol__account_cycles(u64 addr, u64 start,
				  struct symbol *sym, unsigned cycles)
{
	struct cyc_hist *cycles_hist;
	unsigned offset;

	if (sym == NULL)
		return 0;
	cycles_hist = symbol__cycles_hist(sym);
	if (cycles_hist == NULL)
		return -ENOMEM;
	if (addr < sym->start || addr >= sym->end)
		return -ERANGE;

	if (start) {
		if (start < sym->start || start >= sym->end)
			return -ERANGE;
		if (start >= addr)
			start = 0;
	}
	offset = addr - sym->start;
	return __symbol__account_cycles(cycles_hist,
					start ? start - sym->start : 0,
					offset, cycles,
					!!start);
}