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
struct audit_context {int dummy; } ;
struct audit_buffer {int /*<<< orphan*/  gfp_mask; struct audit_context* ctx; int /*<<< orphan*/  skb; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_BUFSIZ ; 
 int /*<<< orphan*/  audit_buffer_cache ; 
 int /*<<< orphan*/  audit_buffer_free (struct audit_buffer*) ; 
 struct audit_buffer* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct audit_buffer *audit_buffer_alloc(struct audit_context *ctx,
					       gfp_t gfp_mask, int type)
{
	struct audit_buffer *ab;

	ab = kmem_cache_alloc(audit_buffer_cache, gfp_mask);
	if (!ab)
		return NULL;

	ab->skb = nlmsg_new(AUDIT_BUFSIZ, gfp_mask);
	if (!ab->skb)
		goto err;
	if (!nlmsg_put(ab->skb, 0, 0, type, 0, 0))
		goto err;

	ab->ctx = ctx;
	ab->gfp_mask = gfp_mask;

	return ab;

err:
	audit_buffer_free(ab);
	return NULL;
}