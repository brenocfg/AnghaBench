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
struct map_iter {struct map_iter* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct map_iter*) ; 

__attribute__((used)) static void map_iter_free(struct map_iter *iter)
{
	if (iter) {
		kfree(iter->key);
		kfree(iter);
	}
}