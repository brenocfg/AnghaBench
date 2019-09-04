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
typedef  int /*<<< orphan*/  time_t ;
struct nfsd_net {int nfsd4_lease; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int max (int,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

__attribute__((used)) static int max_cb_time(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	return max(nn->nfsd4_lease/10, (time_t)1) * HZ;
}