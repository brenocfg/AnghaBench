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
struct svc_expkey {int ek_fsidtype; int /*<<< orphan*/  h; int /*<<< orphan*/  ek_fsid; struct auth_domain* ek_client; } ;
struct cache_req {int dummy; } ;
struct cache_detail {int dummy; } ;
struct auth_domain {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct svc_expkey* ERR_PTR (int) ; 
 int cache_check (struct cache_detail*,int /*<<< orphan*/ *,struct cache_req*) ; 
 int /*<<< orphan*/  key_len (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct svc_expkey* svc_expkey_lookup (struct cache_detail*,struct svc_expkey*) ; 

__attribute__((used)) static struct svc_expkey *
exp_find_key(struct cache_detail *cd, struct auth_domain *clp, int fsid_type,
	     u32 *fsidv, struct cache_req *reqp)
{
	struct svc_expkey key, *ek;
	int err;
	
	if (!clp)
		return ERR_PTR(-ENOENT);

	key.ek_client = clp;
	key.ek_fsidtype = fsid_type;
	memcpy(key.ek_fsid, fsidv, key_len(fsid_type));

	ek = svc_expkey_lookup(cd, &key);
	if (ek == NULL)
		return ERR_PTR(-ENOMEM);
	err = cache_check(cd, &ek->h, reqp);
	if (err)
		return ERR_PTR(err);
	return ek;
}