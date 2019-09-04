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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _write_cam (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

void _clear_cam_entry(struct adapter *padapter, u8 entry)
{
	unsigned char null_sta[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char null_key[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	_write_cam(padapter, entry, 0, null_sta, null_key);
}