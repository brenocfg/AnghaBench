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
struct svc_serv {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_INET ; 
 int svc_create_xprt (struct svc_serv*,char*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int xprt_rdma_bc_up(struct svc_serv *serv, struct net *net)
{
	int ret;

	ret = svc_create_xprt(serv, "rdma-bc", net, PF_INET, 0, 0);
	if (ret < 0)
		return ret;
	return 0;
}