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
typedef  int /*<<< orphan*/  u32 ;
struct vbox_private {scalar_t__ guest_heap; } ;

/* Variables and functions */
 scalar_t__ HOST_FLAGS_OFFSET ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 vbox_get_flags(struct vbox_private *vbox)
{
	return readl(vbox->guest_heap + HOST_FLAGS_OFFSET);
}