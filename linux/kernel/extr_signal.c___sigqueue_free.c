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
struct sigqueue {int flags; TYPE_1__* user; } ;
struct TYPE_2__ {int /*<<< orphan*/  sigpending; } ;

/* Variables and functions */
 int SIGQUEUE_PREALLOC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sigqueue*) ; 
 int /*<<< orphan*/  sigqueue_cachep ; 

__attribute__((used)) static void __sigqueue_free(struct sigqueue *q)
{
	if (q->flags & SIGQUEUE_PREALLOC)
		return;
	atomic_dec(&q->user->sigpending);
	free_uid(q->user);
	kmem_cache_free(sigqueue_cachep, q);
}