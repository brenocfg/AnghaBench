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
struct rocker_wait {int dummy; } ;
struct rocker_desc_info {int dummy; } ;

/* Variables and functions */
 struct rocker_wait* rocker_desc_cookie_ptr_get (struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_wait_destroy (struct rocker_wait*) ; 

__attribute__((used)) static void
rocker_dma_cmd_ring_wait_free(const struct rocker_desc_info *desc_info)
{
	struct rocker_wait *wait = rocker_desc_cookie_ptr_get(desc_info);

	rocker_wait_destroy(wait);
}