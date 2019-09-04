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
struct c2h_evt_hdr {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  scalar_t__ (* c2h_id_filter ) (int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 scalar_t__ _FALSE ; 
 scalar_t__ _SUCCESS ; 
 scalar_t__ c2h_evt_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_c2h_handler (int /*<<< orphan*/ *,struct c2h_evt_hdr*) ; 

s32 c2h_evt_hdl(_adapter *adapter, struct c2h_evt_hdr *c2h_evt, c2h_id_filter filter)
{
	s32 ret = _FAIL;
	u8 buf[16];

	if (!c2h_evt) {
		/* No c2h event in cmd_obj, read c2h event before handling*/
		if (c2h_evt_read(adapter, buf) == _SUCCESS) {
			c2h_evt = (struct c2h_evt_hdr *)buf;
			
			if (filter && filter(c2h_evt->id) == _FALSE)
				goto exit;

			ret = rtw_hal_c2h_handler(adapter, c2h_evt);
		}
	} else {

		if (filter && filter(c2h_evt->id) == _FALSE)
			goto exit;

		ret = rtw_hal_c2h_handler(adapter, c2h_evt);
	}
exit:
	return ret;
}