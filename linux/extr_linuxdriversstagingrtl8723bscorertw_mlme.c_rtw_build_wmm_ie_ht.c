#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int qos_option; } ;
struct TYPE_4__ {TYPE_1__ qospriv; } ;
struct adapter {TYPE_2__ mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _VENDOR_SPECIFIC_IE_ ; 
 int /*<<< orphan*/  _WMM_IE_Length_ ; 
 int /*<<< orphan*/ * rtw_set_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*) ; 

void rtw_build_wmm_ie_ht(struct adapter *padapter, u8 *out_ie, uint *pout_len)
{
	unsigned char WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00};
	int out_len;
	u8 *pframe;

	if (padapter->mlmepriv.qospriv.qos_option == 0) {
		out_len = *pout_len;
		pframe = rtw_set_ie(out_ie+out_len, _VENDOR_SPECIFIC_IE_,
							_WMM_IE_Length_, WMM_IE, pout_len);

		padapter->mlmepriv.qospriv.qos_option = 1;
	}
}