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
struct svc_cacherep {int dummy; } ;
struct nfsd_drc_bucket {int /*<<< orphan*/  cache_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd_reply_cache_free_locked (struct svc_cacherep*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsd_reply_cache_free(struct nfsd_drc_bucket *b, struct svc_cacherep *rp)
{
	spin_lock(&b->cache_lock);
	nfsd_reply_cache_free_locked(rp);
	spin_unlock(&b->cache_lock);
}