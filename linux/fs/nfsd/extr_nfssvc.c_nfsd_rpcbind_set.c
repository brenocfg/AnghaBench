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
typedef  int /*<<< orphan*/  u32 ;
struct svc_program {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_TEST ; 
 int /*<<< orphan*/  net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfsd_vers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svc_generic_rpcbind_set (struct net*,struct svc_program const*,int /*<<< orphan*/ ,int,unsigned short,unsigned short) ; 

__attribute__((used)) static int
nfsd_rpcbind_set(struct net *net, const struct svc_program *progp,
		 u32 version, int family, unsigned short proto,
		 unsigned short port)
{
	if (!nfsd_vers(net_generic(net, nfsd_net_id), version, NFSD_TEST))
		return 0;
	return svc_generic_rpcbind_set(net, progp, version, family,
			proto, port);
}