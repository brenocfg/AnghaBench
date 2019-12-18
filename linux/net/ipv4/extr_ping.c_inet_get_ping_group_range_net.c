#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * range; } ;
struct TYPE_4__ {TYPE_1__ ping_group_range; } ;
struct net {TYPE_2__ ipv4; } ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void inet_get_ping_group_range_net(struct net *net, kgid_t *low,
					  kgid_t *high)
{
	kgid_t *data = net->ipv4.ping_group_range.range;
	unsigned int seq;

	do {
		seq = read_seqbegin(&net->ipv4.ping_group_range.lock);

		*low = data[0];
		*high = data[1];
	} while (read_seqretry(&net->ipv4.ping_group_range.lock, seq));
}