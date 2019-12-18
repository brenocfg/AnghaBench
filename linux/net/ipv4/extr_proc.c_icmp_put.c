#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct net* private; } ;
struct TYPE_5__ {int /*<<< orphan*/  icmp_statistics; TYPE_1__* icmpmsg_statistics; } ;
struct net {TYPE_2__ mib; } ;
typedef  int /*<<< orphan*/  atomic_long_t ;
struct TYPE_6__ {int index; scalar_t__ name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mibs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_MIB_CSUMERRORS ; 
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int /*<<< orphan*/  ICMP_MIB_INMSGS ; 
 int /*<<< orphan*/  ICMP_MIB_OUTERRORS ; 
 int /*<<< orphan*/  ICMP_MIB_OUTMSGS ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 TYPE_3__* icmpmibmap ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  snmp_fold_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icmp_put(struct seq_file *seq)
{
	int i;
	struct net *net = seq->private;
	atomic_long_t *ptr = net->mib.icmpmsg_statistics->mibs;

	seq_puts(seq, "\nIcmp: InMsgs InErrors InCsumErrors");
	for (i = 0; icmpmibmap[i].name; i++)
		seq_printf(seq, " In%s", icmpmibmap[i].name);
	seq_puts(seq, " OutMsgs OutErrors");
	for (i = 0; icmpmibmap[i].name; i++)
		seq_printf(seq, " Out%s", icmpmibmap[i].name);
	seq_printf(seq, "\nIcmp: %lu %lu %lu",
		snmp_fold_field(net->mib.icmp_statistics, ICMP_MIB_INMSGS),
		snmp_fold_field(net->mib.icmp_statistics, ICMP_MIB_INERRORS),
		snmp_fold_field(net->mib.icmp_statistics, ICMP_MIB_CSUMERRORS));
	for (i = 0; icmpmibmap[i].name; i++)
		seq_printf(seq, " %lu",
			   atomic_long_read(ptr + icmpmibmap[i].index));
	seq_printf(seq, " %lu %lu",
		snmp_fold_field(net->mib.icmp_statistics, ICMP_MIB_OUTMSGS),
		snmp_fold_field(net->mib.icmp_statistics, ICMP_MIB_OUTERRORS));
	for (i = 0; icmpmibmap[i].name; i++)
		seq_printf(seq, " %lu",
			   atomic_long_read(ptr + (icmpmibmap[i].index | 0x100)));
}