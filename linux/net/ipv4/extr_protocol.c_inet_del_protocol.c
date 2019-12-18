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
struct net_protocol {int dummy; } ;

/* Variables and functions */
 struct net_protocol const* cmpxchg (struct net_protocol const**,struct net_protocol const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet_protos ; 
 int /*<<< orphan*/  synchronize_net () ; 

int inet_del_protocol(const struct net_protocol *prot, unsigned char protocol)
{
	int ret;

	ret = (cmpxchg((const struct net_protocol **)&inet_protos[protocol],
		       prot, NULL) == prot) ? 0 : -1;

	synchronize_net();

	return ret;
}