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
struct hws_trailer_entry {int clock_base; unsigned long long progusage2; int /*<<< orphan*/ * progusage; } ;

/* Variables and functions */
 int S390_CPUMSF_PAGESZ ; 
 int be64toh (int /*<<< orphan*/ ) ; 
 unsigned long long trailer_timestamp (struct hws_trailer_entry*,int) ; 

__attribute__((used)) static unsigned long long get_trailer_time(const unsigned char *buf)
{
	struct hws_trailer_entry *te;
	unsigned long long aux_time, progusage2;
	bool clock_base;

	te = (struct hws_trailer_entry *)(buf + S390_CPUMSF_PAGESZ
					      - sizeof(*te));

#if __BYTE_ORDER == __LITTLE_ENDIAN
	clock_base = be64toh(te->progusage[0]) >> 63 & 0x1;
	progusage2 = be64toh(te->progusage[1]);
#else
	clock_base = te->clock_base;
	progusage2 = te->progusage2;
#endif
	if (!clock_base)	/* TOD_CLOCK_BASE value missing */
		return 0;

	/* Correct calculation to convert time stamp in trailer entry to
	 * nano seconds (taken from arch/s390 function tod_to_ns()).
	 * TOD_CLOCK_BASE is stored in trailer entry member progusage2.
	 */
	aux_time = trailer_timestamp(te, clock_base) - progusage2;
	aux_time = (aux_time >> 9) * 125 + (((aux_time & 0x1ff) * 125) >> 9);
	return aux_time;
}