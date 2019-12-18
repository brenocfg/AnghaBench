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
typedef  int /*<<< orphan*/  tmp ;
struct symbol {int dummy; } ;
struct TYPE_2__ {struct symbol* sym; } ;
struct hist_entry {TYPE_1__ ms; } ;
struct annotation {double hit_insn; double cover_insn; scalar_t__ total_insn; scalar_t__ hit_cycles; } ;

/* Variables and functions */
 int repsep_snprintf (char*,size_t,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double,double) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static int hist_entry__sym_ipc_snprintf(struct hist_entry *he, char *bf,
					size_t size, unsigned int width)
{

	struct symbol *sym = he->ms.sym;
	struct annotation *notes;
	double ipc = 0.0, coverage = 0.0;
	char tmp[64];

	if (!sym)
		return repsep_snprintf(bf, size, "%-*s", width, "-");

	notes = symbol__annotation(sym);

	if (notes->hit_cycles)
		ipc = notes->hit_insn / ((double)notes->hit_cycles);

	if (notes->total_insn) {
		coverage = notes->cover_insn * 100.0 /
			((double)notes->total_insn);
	}

	snprintf(tmp, sizeof(tmp), "%-5.2f [%5.1f%%]", ipc, coverage);
	return repsep_snprintf(bf, size, "%-*s", width, tmp);
}