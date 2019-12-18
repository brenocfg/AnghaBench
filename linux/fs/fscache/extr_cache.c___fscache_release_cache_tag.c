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
struct fscache_cache_tag {int /*<<< orphan*/  link; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fscache_cache_tag* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_addremove_sem ; 
 int /*<<< orphan*/  kfree (struct fscache_cache_tag*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void __fscache_release_cache_tag(struct fscache_cache_tag *tag)
{
	if (tag != ERR_PTR(-ENOMEM)) {
		down_write(&fscache_addremove_sem);

		if (atomic_dec_and_test(&tag->usage))
			list_del_init(&tag->link);
		else
			tag = NULL;

		up_write(&fscache_addremove_sem);

		kfree(tag);
	}
}