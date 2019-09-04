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
struct uwb_rsv_col_info {int dummy; } ;
struct uwb_rsv_alloc_info {unsigned char* bm; struct uwb_rsv_col_info* ci; } ;

/* Variables and functions */
 int UWB_NUM_ZONES ; 
 int /*<<< orphan*/  uwb_rsv_fill_column_info (unsigned char*,int,struct uwb_rsv_col_info*) ; 

__attribute__((used)) static void get_column_descriptors(struct uwb_rsv_alloc_info *ai)
{
	unsigned char *bm = ai->bm;
	struct uwb_rsv_col_info *ci = ai->ci;
	int col;

	for (col = 1; col < UWB_NUM_ZONES; col++) {
		uwb_rsv_fill_column_info(bm, col, &ci[col]);
	}
}