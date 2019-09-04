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
struct svc_rqst {int /*<<< orphan*/  rq_chandle; int /*<<< orphan*/ * rq_gssclient; int /*<<< orphan*/ * rq_client; } ;
struct svc_export {scalar_t__ ex_nflavors; } ;
struct path {int dummy; } ;
struct nfsd_net {struct cache_detail* svc_export_cache; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct svc_export* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  PTR_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 struct svc_export* exp_get_by_name (struct cache_detail*,int /*<<< orphan*/ *,struct path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

struct svc_export *
rqst_exp_get_by_name(struct svc_rqst *rqstp, struct path *path)
{
	struct svc_export *gssexp, *exp = ERR_PTR(-ENOENT);
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	struct cache_detail *cd = nn->svc_export_cache;

	if (rqstp->rq_client == NULL)
		goto gss;

	/* First try the auth_unix client: */
	exp = exp_get_by_name(cd, rqstp->rq_client, path, &rqstp->rq_chandle);
	if (PTR_ERR(exp) == -ENOENT)
		goto gss;
	if (IS_ERR(exp))
		return exp;
	/* If it has secinfo, assume there are no gss/... clients */
	if (exp->ex_nflavors > 0)
		return exp;
gss:
	/* Otherwise, try falling back on gss client */
	if (rqstp->rq_gssclient == NULL)
		return exp;
	gssexp = exp_get_by_name(cd, rqstp->rq_gssclient, path, &rqstp->rq_chandle);
	if (PTR_ERR(gssexp) == -ENOENT)
		return exp;
	if (!IS_ERR(exp))
		exp_put(exp);
	return gssexp;
}