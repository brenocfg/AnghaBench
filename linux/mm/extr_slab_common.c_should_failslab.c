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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ __should_failslab (struct kmem_cache*,int /*<<< orphan*/ ) ; 

int should_failslab(struct kmem_cache *s, gfp_t gfpflags)
{
	if (__should_failslab(s, gfpflags))
		return -ENOMEM;
	return 0;
}