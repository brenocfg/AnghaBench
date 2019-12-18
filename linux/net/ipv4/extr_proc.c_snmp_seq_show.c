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

/* Variables and functions */
 int /*<<< orphan*/  icmp_put (struct seq_file*) ; 
 int /*<<< orphan*/  icmpmsg_put (struct seq_file*) ; 
 int /*<<< orphan*/  snmp_seq_show_ipstats (struct seq_file*,void*) ; 
 int /*<<< orphan*/  snmp_seq_show_tcp_udp (struct seq_file*,void*) ; 

__attribute__((used)) static int snmp_seq_show(struct seq_file *seq, void *v)
{
	snmp_seq_show_ipstats(seq, v);

	icmp_put(seq);	/* RFC 2011 compatibility */
	icmpmsg_put(seq);

	snmp_seq_show_tcp_udp(seq, v);

	return 0;
}