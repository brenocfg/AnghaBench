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
struct TYPE_2__ {int /*<<< orphan*/ * bh_cache; } ;

/* Variables and functions */
 TYPE_1__ g_jbh ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 

void
ext2_destroy_bh()
{
    if (g_jbh.bh_cache) {
        kmem_cache_destroy(g_jbh.bh_cache);
        g_jbh.bh_cache = NULL;
    }
}