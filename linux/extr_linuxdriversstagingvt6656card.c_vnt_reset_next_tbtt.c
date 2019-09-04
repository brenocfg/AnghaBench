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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_REQUEST_TBTT ; 
 int /*<<< orphan*/  MESSAGE_TYPE_SET_TSFTBTT ; 
 int /*<<< orphan*/  vnt_clear_current_tsf (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int vnt_get_next_tbtt (int,int /*<<< orphan*/ ) ; 

void vnt_reset_next_tbtt(struct vnt_private *priv, u16 beacon_interval)
{
	u64 next_tbtt = 0;
	u8 data[8];

	vnt_clear_current_tsf(priv);

	next_tbtt = vnt_get_next_tbtt(next_tbtt, beacon_interval);

	data[0] = (u8)next_tbtt;
	data[1] = (u8)(next_tbtt >> 8);
	data[2] = (u8)(next_tbtt >> 16);
	data[3] = (u8)(next_tbtt >> 24);
	data[4] = (u8)(next_tbtt >> 32);
	data[5] = (u8)(next_tbtt >> 40);
	data[6] = (u8)(next_tbtt >> 48);
	data[7] = (u8)(next_tbtt >> 56);

	vnt_control_out(priv, MESSAGE_TYPE_SET_TSFTBTT,
			MESSAGE_REQUEST_TBTT, 0, 8, data);
}