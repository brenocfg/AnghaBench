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
typedef  size_t uint ;
struct brcms_hardware {size_t* xmtfifo_sz; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFIFO ; 

int brcms_b_xmtfifo_sz_get(struct brcms_hardware *wlc_hw, uint fifo,
			   uint *blocks)
{
	if (fifo >= NFIFO)
		return -EINVAL;

	*blocks = wlc_hw->xmtfifo_sz[fifo];

	return 0;
}