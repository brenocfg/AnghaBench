#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct thread {int dummy; } ;
struct symbol {scalar_t__ start; scalar_t__ end; char* name; } ;
struct perf_event_attr {int dummy; } ;
struct addr_location {scalar_t__ addr; int cpu; struct symbol* sym; TYPE_1__* map; } ;
typedef  int /*<<< orphan*/  al ;
struct TYPE_3__ {int start; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ PRINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCLINE ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 struct symbol* map__find_symbol (TYPE_1__*,scalar_t__) ; 
 scalar_t__ map__fprintf_srcline (TYPE_1__*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct addr_location*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

__attribute__((used)) static int ip__fprintf_sym(uint64_t addr, struct thread *thread,
			   u8 cpumode, int cpu, struct symbol **lastsym,
			   struct perf_event_attr *attr, FILE *fp)
{
	struct addr_location al;
	int off, printed = 0;

	memset(&al, 0, sizeof(al));

	thread__find_map(thread, cpumode, addr, &al);

	if ((*lastsym) && al.addr >= (*lastsym)->start && al.addr < (*lastsym)->end)
		return 0;

	al.cpu = cpu;
	al.sym = NULL;
	if (al.map)
		al.sym = map__find_symbol(al.map, al.addr);

	if (!al.sym)
		return 0;

	if (al.addr < al.sym->end)
		off = al.addr - al.sym->start;
	else
		off = al.addr - al.map->start - al.sym->start;
	printed += fprintf(fp, "\t%s", al.sym->name);
	if (off)
		printed += fprintf(fp, "%+d", off);
	printed += fprintf(fp, ":");
	if (PRINT_FIELD(SRCLINE))
		printed += map__fprintf_srcline(al.map, al.addr, "\t", fp);
	printed += fprintf(fp, "\n");
	*lastsym = al.sym;

	return printed;
}