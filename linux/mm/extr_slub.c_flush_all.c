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
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  flush_cpu_slab ; 
 int /*<<< orphan*/  has_cpu_slab ; 
 int /*<<< orphan*/  on_each_cpu_cond (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kmem_cache*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_all(struct kmem_cache *s)
{
	on_each_cpu_cond(has_cpu_slab, flush_cpu_slab, s, 1, GFP_ATOMIC);
}