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
typedef  int u32 ;
struct tegra_xusb_mbox_msg {int cmd; int data; } ;

/* Variables and functions */
 int CMD_DATA_MASK ; 
 int CMD_DATA_SHIFT ; 
 int CMD_TYPE_MASK ; 
 int CMD_TYPE_SHIFT ; 

__attribute__((used)) static inline u32 tegra_xusb_mbox_pack(const struct tegra_xusb_mbox_msg *msg)
{
	return (msg->cmd & CMD_TYPE_MASK) << CMD_TYPE_SHIFT |
	       (msg->data & CMD_DATA_MASK) << CMD_DATA_SHIFT;
}