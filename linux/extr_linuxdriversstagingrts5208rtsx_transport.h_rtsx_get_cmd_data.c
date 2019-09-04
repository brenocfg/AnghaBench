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
struct rtsx_chip {scalar_t__ host_cmds_ptr; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *rtsx_get_cmd_data(struct rtsx_chip *chip)
{
#ifdef CMD_USING_SG
	return (u8 *)(chip->host_sg_tbl_ptr);
#else
	return (u8 *)(chip->host_cmds_ptr);
#endif
}