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
struct rhashtable {int dummy; } ;

/* Variables and functions */
 void rhashtable_free_and_destroy (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rhashtable_destroy(struct rhashtable *ht)
{
	return rhashtable_free_and_destroy(ht, NULL, NULL);
}