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
struct svc_export {int /*<<< orphan*/  h; int /*<<< orphan*/  ek_path; } ;
struct svc_expkey {int /*<<< orphan*/  h; int /*<<< orphan*/  ek_path; } ;
struct nfsd_net {int /*<<< orphan*/  svc_expkey_cache; } ;
struct cache_req {int dummy; } ;
struct cache_detail {int /*<<< orphan*/  net; } ;
struct auth_domain {int dummy; } ;

/* Variables and functions */
 struct svc_export* ERR_CAST (struct svc_export*) ; 
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct svc_export* exp_find_key (int /*<<< orphan*/ ,struct auth_domain*,int,int /*<<< orphan*/ *,struct cache_req*) ; 
 struct svc_export* exp_get_by_name (struct cache_detail*,struct auth_domain*,int /*<<< orphan*/ *,struct cache_req*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

__attribute__((used)) static struct svc_export *exp_find(struct cache_detail *cd,
				   struct auth_domain *clp, int fsid_type,
				   u32 *fsidv, struct cache_req *reqp)
{
	struct svc_export *exp;
	struct nfsd_net *nn = net_generic(cd->net, nfsd_net_id);
	struct svc_expkey *ek = exp_find_key(nn->svc_expkey_cache, clp, fsid_type, fsidv, reqp);
	if (IS_ERR(ek))
		return ERR_CAST(ek);

	exp = exp_get_by_name(cd, clp, &ek->ek_path, reqp);
	cache_put(&ek->h, nn->svc_expkey_cache);

	if (IS_ERR(exp))
		return ERR_CAST(exp);
	return exp;
}