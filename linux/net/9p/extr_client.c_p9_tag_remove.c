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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;
struct p9_req_t {TYPE_1__ tc; } ;
struct p9_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct p9_client*,struct p9_req_t*,int /*<<< orphan*/ ) ; 
 int p9_req_put (struct p9_req_t*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int p9_tag_remove(struct p9_client *c, struct p9_req_t *r)
{
	unsigned long flags;
	u16 tag = r->tc.tag;

	p9_debug(P9_DEBUG_MUX, "clnt %p req %p tag: %d\n", c, r, tag);
	spin_lock_irqsave(&c->lock, flags);
	idr_remove(&c->reqs, tag);
	spin_unlock_irqrestore(&c->lock, flags);
	return p9_req_put(r);
}