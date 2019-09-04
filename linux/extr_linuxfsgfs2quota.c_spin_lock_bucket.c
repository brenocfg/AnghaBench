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
 int /*<<< orphan*/  hlist_bl_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * qd_hash_table ; 

__attribute__((used)) static inline void spin_lock_bucket(unsigned int hash)
{
        hlist_bl_lock(&qd_hash_table[hash]);
}