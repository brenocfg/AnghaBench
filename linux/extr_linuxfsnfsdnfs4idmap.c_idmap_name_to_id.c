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
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  nametoid_cache; } ;
struct ent {int type; char* name; int id; int /*<<< orphan*/  h; int /*<<< orphan*/  authname; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int idmap_lookup (struct svc_rqst*,int /*<<< orphan*/ ,struct ent*,int /*<<< orphan*/ ,struct ent**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  nametoid_lookup ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfserr_badowner ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int /*<<< orphan*/  rqst_authname (struct svc_rqst*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __be32
idmap_name_to_id(struct svc_rqst *rqstp, int type, const char *name, u32 namelen,
		u32 *id)
{
	struct ent *item, key = {
		.type = type,
	};
	int ret;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	if (namelen + 1 > sizeof(key.name))
		return nfserr_badowner;
	memcpy(key.name, name, namelen);
	key.name[namelen] = '\0';
	strlcpy(key.authname, rqst_authname(rqstp), sizeof(key.authname));
	ret = idmap_lookup(rqstp, nametoid_lookup, &key, nn->nametoid_cache, &item);
	if (ret == -ENOENT)
		return nfserr_badowner;
	if (ret)
		return nfserrno(ret);
	*id = item->id;
	cache_put(&item->h, nn->nametoid_cache);
	return 0;
}