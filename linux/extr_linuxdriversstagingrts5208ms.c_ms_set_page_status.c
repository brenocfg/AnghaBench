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
typedef  int u16 ;

/* Variables and functions */
 int MS_EXTRA_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 scalar_t__ setPS_NG ; 

__attribute__((used)) static void ms_set_page_status(u16 log_blk, u8 type, u8 *extra, int extra_len)
{
	if (!extra || (extra_len < MS_EXTRA_SIZE))
		return;

	memset(extra, 0xFF, MS_EXTRA_SIZE);

	if (type == setPS_NG) {
		/* set page status as 1:NG,and block status keep 1:OK */
		extra[0] = 0xB8;
	} else {
		/* set page status as 0:Data Error,and block status keep 1:OK */
		extra[0] = 0x98;
	}

	extra[2] = (u8)(log_blk >> 8);
	extra[3] = (u8)log_blk;
}