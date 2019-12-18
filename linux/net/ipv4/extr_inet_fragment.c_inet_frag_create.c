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
struct inet_frags {int /*<<< orphan*/  rhash_params; } ;
struct inet_frag_queue {int /*<<< orphan*/  flags; int /*<<< orphan*/  node; int /*<<< orphan*/  key; int /*<<< orphan*/  timer; } ;
struct fqdir {int /*<<< orphan*/  rhashtable; scalar_t__ timeout; struct inet_frags* f; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inet_frag_queue* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INET_FRAG_COMPLETE ; 
 struct inet_frag_queue* inet_frag_alloc (struct fqdir*,struct inet_frags*,void*) ; 
 int /*<<< orphan*/  inet_frag_destroy (struct inet_frag_queue*) ; 
 int /*<<< orphan*/  inet_frag_kill (struct inet_frag_queue*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct inet_frag_queue* rhashtable_lookup_get_insert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inet_frag_queue *inet_frag_create(struct fqdir *fqdir,
						void *arg,
						struct inet_frag_queue **prev)
{
	struct inet_frags *f = fqdir->f;
	struct inet_frag_queue *q;

	q = inet_frag_alloc(fqdir, f, arg);
	if (!q) {
		*prev = ERR_PTR(-ENOMEM);
		return NULL;
	}
	mod_timer(&q->timer, jiffies + fqdir->timeout);

	*prev = rhashtable_lookup_get_insert_key(&fqdir->rhashtable, &q->key,
						 &q->node, f->rhash_params);
	if (*prev) {
		q->flags |= INET_FRAG_COMPLETE;
		inet_frag_kill(q);
		inet_frag_destroy(q);
		return NULL;
	}
	return q;
}