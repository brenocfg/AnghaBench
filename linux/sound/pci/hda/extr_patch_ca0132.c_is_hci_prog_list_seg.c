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
struct dsp_image_seg {scalar_t__ chip_addr; } ;

/* Variables and functions */
 scalar_t__ g_chip_addr_magic_value ; 

__attribute__((used)) static bool is_hci_prog_list_seg(const struct dsp_image_seg *p)
{
	return g_chip_addr_magic_value == p->chip_addr;
}