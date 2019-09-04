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
struct hws_trailer_entry {int bsdes; int /*<<< orphan*/ * progusage; int /*<<< orphan*/  progusage2; int /*<<< orphan*/  clock_base; int /*<<< orphan*/  overflow; int /*<<< orphan*/  dsdes; scalar_t__ t; scalar_t__ a; scalar_t__ f; } ;
struct hws_basic_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t,float,char,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  trailer_timestamp (struct hws_trailer_entry*) ; 

__attribute__((used)) static bool s390_cpumsf_trailer_show(const char *color, size_t pos,
				     struct hws_trailer_entry *te)
{
	if (te->bsdes != sizeof(struct hws_basic_entry)) {
		pr_err("Invalid AUX trace trailer entry [%#08zx]\n", pos);
		return false;
	}
	color_fprintf(stdout, color, "    [%#08zx] Trailer %c%c%c bsdes:%d"
		      " dsdes:%d Overflow:%lld Time:%#llx\n"
		      "\t\tC:%d TOD:%#lx 1:%#llx 2:%#llx\n",
		      pos,
		      te->f ? 'F' : ' ',
		      te->a ? 'A' : ' ',
		      te->t ? 'T' : ' ',
		      te->bsdes, te->dsdes, te->overflow,
		      trailer_timestamp(te), te->clock_base, te->progusage2,
		      te->progusage[0], te->progusage[1]);
	return true;
}