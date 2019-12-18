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
struct cf_trailer_entry {void* mach_type; void* tod_base; void* progusage3; void* progusage2; void* progusage1; void* timestamp; void* cpu_speed; void* csvn; void* cfvn; scalar_t__ lcda; scalar_t__ caca; scalar_t__ mtda; scalar_t__ speed; scalar_t__ clock_base; void* res2; void* res1; void* flags; } ;

/* Variables and functions */
 void* be16_to_cpu (void*) ; 
 void* be32_to_cpu (void*) ; 
 void* be64_to_cpu (void*) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t,char,char,char,char,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void s390_cpumcfdg_dumptrail(const char *color, size_t offset,
				    struct cf_trailer_entry *tep)
{
	struct cf_trailer_entry  te;

	te.flags = be64_to_cpu(tep->flags);
	te.cfvn = be16_to_cpu(tep->cfvn);
	te.csvn = be16_to_cpu(tep->csvn);
	te.cpu_speed = be32_to_cpu(tep->cpu_speed);
	te.timestamp = be64_to_cpu(tep->timestamp);
	te.progusage1 = be64_to_cpu(tep->progusage1);
	te.progusage2 = be64_to_cpu(tep->progusage2);
	te.progusage3 = be64_to_cpu(tep->progusage3);
	te.tod_base = be64_to_cpu(tep->tod_base);
	te.mach_type = be16_to_cpu(tep->mach_type);
	te.res1 = be16_to_cpu(tep->res1);
	te.res2 = be32_to_cpu(tep->res2);

	color_fprintf(stdout, color, "    [%#08zx] Trailer:%c%c%c%c%c"
		      " Cfvn:%d Csvn:%d Speed:%d TOD:%#llx\n",
		      offset, te.clock_base ? 'T' : ' ',
		      te.speed ? 'S' : ' ', te.mtda ? 'M' : ' ',
		      te.caca ? 'C' : ' ', te.lcda ? 'L' : ' ',
		      te.cfvn, te.csvn, te.cpu_speed, te.timestamp);
	color_fprintf(stdout, color, "\t\t1:%lx 2:%lx 3:%lx TOD-Base:%#llx"
		      " Type:%x\n\n",
		      te.progusage1, te.progusage2, te.progusage3,
		      te.tod_base, te.mach_type);
}