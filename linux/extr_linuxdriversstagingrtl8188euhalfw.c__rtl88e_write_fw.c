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
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int FW_8192C_PAGE_SIZE ; 
 int /*<<< orphan*/  _rtl88e_fw_page_write (struct adapter*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _rtl88e_write_fw(struct adapter *adapt, u8 *buffer, u32 size)
{
	u8 *buf_ptr = buffer;
	u32 page_no, remain;
	u32 page, offset;

	page_no = size / FW_8192C_PAGE_SIZE;
	remain = size % FW_8192C_PAGE_SIZE;

	for (page = 0; page < page_no; page++) {
		offset = page * FW_8192C_PAGE_SIZE;
		_rtl88e_fw_page_write(adapt, page, (buf_ptr + offset),
				      FW_8192C_PAGE_SIZE);
	}

	if (remain) {
		offset = page_no * FW_8192C_PAGE_SIZE;
		page = page_no;
		_rtl88e_fw_page_write(adapt, page, (buf_ptr + offset), remain);
	}
}