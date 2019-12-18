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
struct virtual_item {int vi_item_len; } ;

/* Variables and functions */
 int IH_SIZE ; 

__attribute__((used)) static int sd_unit_num(struct virtual_item *vi)
{
	return vi->vi_item_len - IH_SIZE;
}