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
struct velocity_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  velocity_free_dma_rings (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_free_rd_ring (struct velocity_info*) ; 
 int /*<<< orphan*/  velocity_free_td_ring (struct velocity_info*) ; 

__attribute__((used)) static void velocity_free_rings(struct velocity_info *vptr)
{
	velocity_free_td_ring(vptr);
	velocity_free_rd_ring(vptr);
	velocity_free_dma_rings(vptr);
}