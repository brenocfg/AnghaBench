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
struct hash_iter {int entry; scalar_t__ bucket; struct hash const* hash; } ;
struct hash {int dummy; } ;

/* Variables and functions */

void hash_iter_init(const struct hash *hash, struct hash_iter *iter)
{
    iter->hash = hash;
    iter->bucket = 0;
    iter->entry = -1;
}