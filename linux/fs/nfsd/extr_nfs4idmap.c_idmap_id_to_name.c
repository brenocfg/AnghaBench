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
struct xdr_stream {int dummy; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  idtoname_cache; } ;
struct ent {int type; int /*<<< orphan*/  h; int /*<<< orphan*/  name; int /*<<< orphan*/  authname; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 int IDMAP_NAMESZ ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_ascii_id (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int idmap_lookup (struct svc_rqst*,int /*<<< orphan*/ ,struct ent*,int /*<<< orphan*/ ,struct ent**) ; 
 int /*<<< orphan*/  idtoname_lookup ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int /*<<< orphan*/  rqst_authname (struct svc_rqst*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 idmap_id_to_name(struct xdr_stream *xdr,
			       struct svc_rqst *rqstp, int type, u32 id)
{
	struct ent *item, key = {
		.id = id,
		.type = type,
	};
	__be32 *p;
	int ret;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	strlcpy(key.authname, rqst_authname(rqstp), sizeof(key.authname));
	ret = idmap_lookup(rqstp, idtoname_lookup, &key, nn->idtoname_cache, &item);
	if (ret == -ENOENT)
		return encode_ascii_id(xdr, id);
	if (ret)
		return nfserrno(ret);
	ret = strlen(item->name);
	WARN_ON_ONCE(ret > IDMAP_NAMESZ);
	p = xdr_reserve_space(xdr, ret + 4);
	if (!p)
		return nfserr_resource;
	p = xdr_encode_opaque(p, item->name, ret);
	cache_put(&item->h, nn->idtoname_cache);
	return 0;
}