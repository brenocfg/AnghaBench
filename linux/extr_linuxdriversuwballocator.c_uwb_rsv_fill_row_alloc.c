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
struct uwb_rsv_row_info {int* avail; int used_rows; } ;
struct uwb_rsv_alloc_info {unsigned char* bm; scalar_t__ unsafe_allocated_mases; scalar_t__ safe_allocated_mases; scalar_t__ total_allocated_mases; struct uwb_rsv_row_info ri; } ;

/* Variables and functions */
 int UWB_MAS_PER_ZONE ; 
 int UWB_NUM_ZONES ; 
 unsigned char UWB_RSV_MAS_NOT_AVAIL ; 
 unsigned char UWB_RSV_MAS_SAFE ; 
 unsigned char UWB_RSV_MAS_UNSAFE ; 

__attribute__((used)) static void uwb_rsv_fill_row_alloc(struct uwb_rsv_alloc_info *ai)
{
	int mas, col, rows;
	unsigned char *bm = ai->bm;
	struct uwb_rsv_row_info *ri = &ai->ri;
	unsigned char c;

	rows = 1;
	c = UWB_RSV_MAS_SAFE;
	for (mas = UWB_MAS_PER_ZONE - 1; mas >= 0; mas--) {
		if (ri->avail[mas] == 1) {
      
			if (rows > ri->used_rows) {
				break;
			} else if (rows > 7) {
				c = UWB_RSV_MAS_UNSAFE;
			}

			for (col = 0; col < UWB_NUM_ZONES; col++) {
				if (bm[col * UWB_NUM_ZONES + mas] != UWB_RSV_MAS_NOT_AVAIL) {
					bm[col * UWB_NUM_ZONES + mas] = c;
					if(c == UWB_RSV_MAS_SAFE)
						ai->safe_allocated_mases++;
					else
						ai->unsafe_allocated_mases++;
				}
			}
			rows++;
		}
	}
	ai->total_allocated_mases = ai->safe_allocated_mases + ai->unsafe_allocated_mases;
}