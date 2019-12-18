#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ cr_flavor; } ;
struct svc_rqst {TYPE_1__ rq_cred; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_GSS ; 
 int /*<<< orphan*/  idmap_name_to_id (struct svc_rqst*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_disable_idmapping ; 
 scalar_t__ numeric_name_to_id (struct svc_rqst*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
do_name_to_id(struct svc_rqst *rqstp, int type, const char *name, u32 namelen, u32 *id)
{
	if (nfs4_disable_idmapping && rqstp->rq_cred.cr_flavor < RPC_AUTH_GSS)
		if (numeric_name_to_id(rqstp, type, name, namelen, id))
			return 0;
		/*
		 * otherwise, fall through and try idmapping, for
		 * backwards compatibility with clients sending names:
		 */
	return idmap_name_to_id(rqstp, type, name, namelen, id);
}