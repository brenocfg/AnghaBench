#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int start_col; int safe_mas_per_col; int unsafe_mas_per_col; scalar_t__ interval; } ;
struct uwb_rsv_col_info {TYPE_1__ csi; } ;
struct uwb_rsv_alloc_info {unsigned char* bm; struct uwb_rsv_col_info* ci; } ;

/* Variables and functions */
 int UWB_MAS_PER_ZONE ; 
 int UWB_NUM_ZONES ; 
 unsigned char UWB_RSV_MAS_SAFE ; 
 unsigned char UWB_RSV_MAS_UNSAFE ; 

__attribute__((used)) static void uwb_rsv_fill_column_alloc(struct uwb_rsv_alloc_info *ai)
{
	int col, mas, safe_mas, unsafe_mas;
	unsigned char *bm = ai->bm;
	struct uwb_rsv_col_info *ci = ai->ci;
	unsigned char c;

	for (col = ci->csi.start_col; col < UWB_NUM_ZONES; col += ci->csi.interval) {
    
		safe_mas   = ci->csi.safe_mas_per_col;
		unsafe_mas = ci->csi.unsafe_mas_per_col;
    
		for (mas = 0; mas < UWB_MAS_PER_ZONE; mas++ ) {
			if (bm[col * UWB_MAS_PER_ZONE + mas] == 0) {
	
				if (safe_mas > 0) {
					safe_mas--;
					c = UWB_RSV_MAS_SAFE;
				} else if (unsafe_mas > 0) {
					unsafe_mas--;
					c = UWB_RSV_MAS_UNSAFE;
				} else {
					break;
				}
				bm[col * UWB_MAS_PER_ZONE + mas] = c;
			}
		}
	}
}