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
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  atomic_long_t ;

/* Variables and functions */
 int ICMP6MSG_MIB_MAX ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 char** icmp6type2name ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

__attribute__((used)) static void snmp6_seq_show_icmpv6msg(struct seq_file *seq, atomic_long_t *smib)
{
	char name[32];
	int i;

	/* print by name -- deprecated items */
	for (i = 0; i < ICMP6MSG_MIB_MAX; i++) {
		int icmptype;
		const char *p;

		icmptype = i & 0xff;
		p = icmp6type2name[icmptype];
		if (!p)	/* don't print un-named types here */
			continue;
		snprintf(name, sizeof(name), "Icmp6%s%s",
			i & 0x100 ? "Out" : "In", p);
		seq_printf(seq, "%-32s\t%lu\n", name,
			   atomic_long_read(smib + i));
	}

	/* print by number (nonzero only) - ICMPMsgStat format */
	for (i = 0; i < ICMP6MSG_MIB_MAX; i++) {
		unsigned long val;

		val = atomic_long_read(smib + i);
		if (!val)
			continue;
		snprintf(name, sizeof(name), "Icmp6%sType%u",
			i & 0x100 ?  "Out" : "In", i & 0xff);
		seq_printf(seq, "%-32s\t%lu\n", name, val);
	}
}