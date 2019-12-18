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
struct inet_frags {int /*<<< orphan*/  completion; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  frags_cachep; int /*<<< orphan*/  qsize; int /*<<< orphan*/  frags_cache_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

int inet_frags_init(struct inet_frags *f)
{
	f->frags_cachep = kmem_cache_create(f->frags_cache_name, f->qsize, 0, 0,
					    NULL);
	if (!f->frags_cachep)
		return -ENOMEM;

	refcount_set(&f->refcnt, 1);
	init_completion(&f->completion);
	return 0;
}