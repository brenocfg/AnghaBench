#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct net* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  sctp_statistics; } ;
struct net {TYPE_1__ sctp; } ;
struct TYPE_5__ {scalar_t__ name; } ;

/* Variables and functions */
 int SCTP_MIB_MAX ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sctp_snmp_list ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  snmp_get_cpu_field_batch (unsigned long*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_snmp_seq_show(struct seq_file *seq, void *v)
{
	unsigned long buff[SCTP_MIB_MAX];
	struct net *net = seq->private;
	int i;

	memset(buff, 0, sizeof(unsigned long) * SCTP_MIB_MAX);

	snmp_get_cpu_field_batch(buff, sctp_snmp_list,
				 net->sctp.sctp_statistics);
	for (i = 0; sctp_snmp_list[i].name; i++)
		seq_printf(seq, "%-32s\t%ld\n", sctp_snmp_list[i].name,
						buff[i]);

	return 0;
}