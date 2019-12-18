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
struct sctp_bind_bucket {int /*<<< orphan*/  node; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bind_bucket ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sctp_bind_bucket*) ; 
 int /*<<< orphan*/  sctp_bucket_cachep ; 

__attribute__((used)) static void sctp_bucket_destroy(struct sctp_bind_bucket *pp)
{
	if (pp && hlist_empty(&pp->owner)) {
		__hlist_del(&pp->node);
		kmem_cache_free(sctp_bucket_cachep, pp);
		SCTP_DBG_OBJCNT_DEC(bind_bucket);
	}
}