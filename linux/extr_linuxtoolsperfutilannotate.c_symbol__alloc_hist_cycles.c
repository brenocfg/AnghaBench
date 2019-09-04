#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct cyc_hist {int dummy; } ;
struct annotation {TYPE_1__* src; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cycles_hist; } ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (size_t const,int) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 
 size_t symbol__size (struct symbol*) ; 

__attribute__((used)) static int symbol__alloc_hist_cycles(struct symbol *sym)
{
	struct annotation *notes = symbol__annotation(sym);
	const size_t size = symbol__size(sym);

	notes->src->cycles_hist = calloc(size, sizeof(struct cyc_hist));
	if (notes->src->cycles_hist == NULL)
		return -1;
	return 0;
}