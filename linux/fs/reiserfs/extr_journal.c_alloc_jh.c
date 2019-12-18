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
struct reiserfs_jh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct reiserfs_jh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_reiserfs_jh ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static struct reiserfs_jh *alloc_jh(void)
{
	struct reiserfs_jh *jh;
	while (1) {
		jh = kmalloc(sizeof(*jh), GFP_NOFS);
		if (jh) {
			atomic_inc(&nr_reiserfs_jh);
			return jh;
		}
		yield();
	}
}