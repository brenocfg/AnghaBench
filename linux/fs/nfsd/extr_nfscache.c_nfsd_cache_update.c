#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {struct kvec* head; } ;
struct svc_rqst {int /*<<< orphan*/  rq_flags; TYPE_1__ rq_res; struct svc_cacherep* rq_cacherep; } ;
struct kvec {int iov_len; scalar_t__ iov_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  k_xid; } ;
struct svc_cacherep {int c_type; int /*<<< orphan*/  c_state; int /*<<< orphan*/  c_secure; struct kvec c_replvec; int /*<<< orphan*/  c_replstat; TYPE_2__ c_key; } ;
struct nfsd_net {size_t drc_mem_usage; struct nfsd_drc_bucket* drc_hashtbl; } ;
struct nfsd_drc_bucket {int /*<<< orphan*/  cache_lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RC_DONE ; 
#define  RC_NOCACHE 130 
#define  RC_REPLBUFF 129 
#define  RC_REPLSTAT 128 
 int /*<<< orphan*/  RQ_SECURE ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 scalar_t__ kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lru_put_end (struct nfsd_drc_bucket*,struct svc_cacherep*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nfsd_cache_hash (int /*<<< orphan*/ ,struct nfsd_net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfsd_reply_cache_free (struct nfsd_drc_bucket*,struct svc_cacherep*,struct nfsd_net*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nfsd_cache_update(struct svc_rqst *rqstp, int cachetype, __be32 *statp)
{
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	struct svc_cacherep *rp = rqstp->rq_cacherep;
	struct kvec	*resv = &rqstp->rq_res.head[0], *cachv;
	u32		hash;
	struct nfsd_drc_bucket *b;
	int		len;
	size_t		bufsize = 0;

	if (!rp)
		return;

	hash = nfsd_cache_hash(rp->c_key.k_xid, nn);
	b = &nn->drc_hashtbl[hash];

	len = resv->iov_len - ((char*)statp - (char*)resv->iov_base);
	len >>= 2;

	/* Don't cache excessive amounts of data and XDR failures */
	if (!statp || len > (256 >> 2)) {
		nfsd_reply_cache_free(b, rp, nn);
		return;
	}

	switch (cachetype) {
	case RC_REPLSTAT:
		if (len != 1)
			printk("nfsd: RC_REPLSTAT/reply len %d!\n",len);
		rp->c_replstat = *statp;
		break;
	case RC_REPLBUFF:
		cachv = &rp->c_replvec;
		bufsize = len << 2;
		cachv->iov_base = kmalloc(bufsize, GFP_KERNEL);
		if (!cachv->iov_base) {
			nfsd_reply_cache_free(b, rp, nn);
			return;
		}
		cachv->iov_len = bufsize;
		memcpy(cachv->iov_base, statp, bufsize);
		break;
	case RC_NOCACHE:
		nfsd_reply_cache_free(b, rp, nn);
		return;
	}
	spin_lock(&b->cache_lock);
	nn->drc_mem_usage += bufsize;
	lru_put_end(b, rp);
	rp->c_secure = test_bit(RQ_SECURE, &rqstp->rq_flags);
	rp->c_type = cachetype;
	rp->c_state = RC_DONE;
	spin_unlock(&b->cache_lock);
	return;
}