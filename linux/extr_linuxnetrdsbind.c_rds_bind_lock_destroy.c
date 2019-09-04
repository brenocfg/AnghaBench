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

/* Variables and functions */
 int /*<<< orphan*/  bind_hash_table ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

void rds_bind_lock_destroy(void)
{
	rhashtable_destroy(&bind_hash_table);
}