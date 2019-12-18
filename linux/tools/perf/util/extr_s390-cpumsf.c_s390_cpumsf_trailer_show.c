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
struct hws_trailer_entry {int flags; unsigned long long f; unsigned long long a; unsigned long long t; int bsdes; int overflow; int clock_base; int* progusage; int progusage2; void* dsdes; int /*<<< orphan*/  timestamp; } ;
struct hws_basic_entry {int dummy; } ;
typedef  int /*<<< orphan*/  local ;

/* Variables and functions */
 void* be16toh (unsigned long long const) ; 
 int be64toh (int) ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,char const*,char*,size_t,float,char,char,int,void*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct hws_trailer_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  trailer_timestamp (struct hws_trailer_entry*,int) ; 

__attribute__((used)) static bool s390_cpumsf_trailer_show(const char *color, size_t pos,
				     struct hws_trailer_entry *te)
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	struct hws_trailer_entry local;
	const unsigned long long flags = be64toh(te->flags);

	memset(&local, 0, sizeof(local));
	local.f = flags >> 63 & 0x1;
	local.a = flags >> 62 & 0x1;
	local.t = flags >> 61 & 0x1;
	local.bsdes = be16toh((flags >> 16 & 0xffff));
	local.dsdes = be16toh((flags & 0xffff));
	memcpy(&local.timestamp, te->timestamp, sizeof(te->timestamp));
	local.overflow = be64toh(te->overflow);
	local.clock_base = be64toh(te->progusage[0]) >> 63 & 1;
	local.progusage2 = be64toh(te->progusage2);
	te = &local;
#endif
	if (te->bsdes != sizeof(struct hws_basic_entry)) {
		pr_err("Invalid AUX trace trailer entry [%#08zx]\n", pos);
		return false;
	}
	color_fprintf(stdout, color, "    [%#08zx] Trailer %c%c%c bsdes:%d"
		      " dsdes:%d Overflow:%lld Time:%#llx\n"
		      "\t\tC:%d TOD:%#lx\n",
		      pos,
		      te->f ? 'F' : ' ',
		      te->a ? 'A' : ' ',
		      te->t ? 'T' : ' ',
		      te->bsdes, te->dsdes, te->overflow,
		      trailer_timestamp(te, te->clock_base),
		      te->clock_base, te->progusage2);
	return true;
}