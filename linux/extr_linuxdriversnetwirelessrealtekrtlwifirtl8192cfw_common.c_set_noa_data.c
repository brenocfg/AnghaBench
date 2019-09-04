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
typedef  scalar_t__ u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_p2p_ps_info {int noa_num; scalar_t__* noa_duration; scalar_t__* noa_interval; scalar_t__* noa_start_time; int* noa_count_type; } ;
struct p2p_ps_offload_t {int noa0_en; int noa1_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TSFTR ; 
 scalar_t__ rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,scalar_t__) ; 

__attribute__((used)) static void set_noa_data(struct rtl_priv *rtlpriv,
			 struct rtl_p2p_ps_info *p2pinfo,
			 struct p2p_ps_offload_t *p2p_ps_offload)
{
	int i;
	u32	start_time, tsf_low;

	/* hw only support 2 set of NoA */
	for (i = 0 ; i < p2pinfo->noa_num ; i++) {
		/* To control the reg setting for which NOA*/
		rtl_write_byte(rtlpriv, 0x5cf, (i << 4));
		if (i == 0)
			p2p_ps_offload->noa0_en = 1;
		else
			p2p_ps_offload->noa1_en = 1;

		/* config P2P NoA Descriptor Register */
		rtl_write_dword(rtlpriv, 0x5E0,
				p2pinfo->noa_duration[i]);
		rtl_write_dword(rtlpriv, 0x5E4,
				p2pinfo->noa_interval[i]);

		/*Get Current TSF value */
		tsf_low = rtl_read_dword(rtlpriv, REG_TSFTR);

		start_time = p2pinfo->noa_start_time[i];
		if (p2pinfo->noa_count_type[i] != 1) {
			while (start_time <= (tsf_low+(50*1024))) {
				start_time += p2pinfo->noa_interval[i];
				if (p2pinfo->noa_count_type[i] != 255)
					p2pinfo->noa_count_type[i]--;
			}
		}
		rtl_write_dword(rtlpriv, 0x5E8, start_time);
		rtl_write_dword(rtlpriv, 0x5EC,
				p2pinfo->noa_count_type[i]);
	}
}