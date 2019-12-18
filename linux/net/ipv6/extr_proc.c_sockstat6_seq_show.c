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
struct TYPE_5__ {TYPE_3__* fqdir; } ;
struct net {TYPE_2__ ipv6; } ;
struct TYPE_4__ {int /*<<< orphan*/  nelems; } ;
struct TYPE_6__ {TYPE_1__ rhashtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_mem_limit (TYPE_3__*) ; 
 int /*<<< orphan*/  rawv6_prot ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sock_prot_inuse_get (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpv6_prot ; 
 int /*<<< orphan*/  udplitev6_prot ; 
 int /*<<< orphan*/  udpv6_prot ; 

__attribute__((used)) static int sockstat6_seq_show(struct seq_file *seq, void *v)
{
	struct net *net = seq->private;

	seq_printf(seq, "TCP6: inuse %d\n",
		       sock_prot_inuse_get(net, &tcpv6_prot));
	seq_printf(seq, "UDP6: inuse %d\n",
		       sock_prot_inuse_get(net, &udpv6_prot));
	seq_printf(seq, "UDPLITE6: inuse %d\n",
			sock_prot_inuse_get(net, &udplitev6_prot));
	seq_printf(seq, "RAW6: inuse %d\n",
		       sock_prot_inuse_get(net, &rawv6_prot));
	seq_printf(seq, "FRAG6: inuse %u memory %lu\n",
		   atomic_read(&net->ipv6.fqdir->rhashtable.nelems),
		   frag_mem_limit(net->ipv6.fqdir));
	return 0;
}