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
struct addr_location {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t __symbol__fprintf_symname_offs (struct symbol const*,struct addr_location const*,int,int,int /*<<< orphan*/ *) ; 

size_t symbol__fprintf_symname_offs(const struct symbol *sym,
				    const struct addr_location *al,
				    FILE *fp)
{
	return __symbol__fprintf_symname_offs(sym, al, false, true, fp);
}