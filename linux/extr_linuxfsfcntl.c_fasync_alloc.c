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
struct fasync_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fasync_cache ; 
 struct fasync_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fasync_struct *fasync_alloc(void)
{
	return kmem_cache_alloc(fasync_cache, GFP_KERNEL);
}