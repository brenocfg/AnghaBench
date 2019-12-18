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
typedef  int /*<<< orphan*/  u32 ;
struct nfs4_filelayout_segment {scalar_t__ stripe_type; int /*<<< orphan*/  generic_hdr; } ;

/* Variables and functions */
 scalar_t__ STRIPE_SPARSE ; 
 int /*<<< orphan*/  nfs4_fl_calc_ds_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 select_bucket_index(struct nfs4_filelayout_segment *fl, u32 j)
{
	if (fl->stripe_type == STRIPE_SPARSE)
		return nfs4_fl_calc_ds_index(&fl->generic_hdr, j);
	else
		return j;
}