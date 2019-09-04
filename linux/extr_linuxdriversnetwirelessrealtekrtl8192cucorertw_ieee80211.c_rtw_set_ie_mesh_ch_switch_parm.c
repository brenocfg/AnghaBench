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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  RTW_PUT_LE16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtw_set_ie (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

inline u8 *rtw_set_ie_mesh_ch_switch_parm(u8 *buf, u32 *buf_len, u8 ttl,
	u8 flags, u16 reason, u16 precedence)
{
	u8 ie_data[6];

	ie_data[0] = ttl;
	ie_data[1] = flags;
	RTW_PUT_LE16((u8*)&ie_data[2], reason);
	RTW_PUT_LE16((u8*)&ie_data[4], precedence);

	return rtw_set_ie(buf, 0x118,  6, ie_data, buf_len);
}