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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_API ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  SET_NO_NEED ; 
 int /*<<< orphan*/  SET_SUCCESS ; 

__attribute__((used)) static u8 phydm_calculate_intf_distance(void *dm_void, u32 bw, u32 fc,
					u32 f_interference,
					u32 *tone_idx_tmp_in)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 bw_up, bw_low;
	u32 int_distance;
	u32 tone_idx_tmp;
	u8 set_result = SET_NO_NEED;

	bw_up = fc + bw / 2;
	bw_low = fc - bw / 2;

	ODM_RT_TRACE(dm, ODM_COMP_API,
		     "[f_l, fc, fh] = [ %d, %d, %d ], f_int = ((%d))\n", bw_low,
		     fc, bw_up, f_interference);

	if (f_interference >= bw_low && f_interference <= bw_up) {
		int_distance = (fc >= f_interference) ? (fc - f_interference) :
							(f_interference - fc);
		tone_idx_tmp =
			(int_distance << 5); /* =10*(int_distance /0.3125) */
		ODM_RT_TRACE(
			dm, ODM_COMP_API,
			"int_distance = ((%d MHz)) Mhz, tone_idx_tmp = ((%d.%d))\n",
			int_distance, (tone_idx_tmp / 10), (tone_idx_tmp % 10));
		*tone_idx_tmp_in = tone_idx_tmp;
		set_result = SET_SUCCESS;
	}

	return set_result;
}