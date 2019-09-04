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
typedef  int u64 ;
typedef  int u32 ;
struct ore_striping_info {int unit_off; int cur_comp; int cur_pg; int par_dev; int dev; int bytes_in_stripe; int first_stripe_start; int offset; int length; int maxdevUnits; int M; scalar_t__ obj_offset; } ;
struct ore_layout {int stripe_unit; int group_width; int group_depth; int parity; int group_count; int mirrors_p1; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int div64_u64 (int,int) ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  div_u64_rem (int,int,int*) ; 
 int lcm (int,int) ; 

void ore_calc_stripe_info(struct ore_layout *layout, u64 file_offset,
			  u64 length, struct ore_striping_info *si)
{
	u32	stripe_unit = layout->stripe_unit;
	u32	group_width = layout->group_width;
	u64	group_depth = layout->group_depth;
	u32	parity      = layout->parity;

	u32	D = group_width - parity;
	u32	U = D * stripe_unit;
	u64	T = U * group_depth;
	u64	S = T * layout->group_count;
	u64	M = div64_u64(file_offset, S);

	/*
	G = (L - (M * S)) / T
	H = (L - (M * S)) % T
	*/
	u64	LmodS = file_offset - M * S;
	u32	G = div64_u64(LmodS, T);
	u64	H = LmodS - G * T;

	u32	N = div_u64(H, U);
	u32	Nlast;

	/* "H - (N * U)" is just "H % U" so it's bound to u32 */
	u32	C = (u32)(H - (N * U)) / stripe_unit + G * group_width;
	u32 first_dev = C - C % group_width;

	div_u64_rem(file_offset, stripe_unit, &si->unit_off);

	si->obj_offset = si->unit_off + (N * stripe_unit) +
				  (M * group_depth * stripe_unit);
	si->cur_comp = C - first_dev;
	si->cur_pg = si->unit_off / PAGE_SIZE;

	if (parity) {
		u32 LCMdP = lcm(group_width, parity) / parity;
		/* R     = N % LCMdP; */
		u32 RxP   = (N % LCMdP) * parity;

		si->par_dev = (group_width + group_width - parity - RxP) %
			      group_width + first_dev;
		si->dev = (group_width + group_width + C - RxP) %
			  group_width + first_dev;
		si->bytes_in_stripe = U;
		si->first_stripe_start = M * S + G * T + N * U;
	} else {
		/* Make the math correct see _prepare_one_group */
		si->par_dev = group_width;
		si->dev = C;
	}

	si->dev *= layout->mirrors_p1;
	si->par_dev *= layout->mirrors_p1;
	si->offset = file_offset;
	si->length = T - H;
	if (si->length > length)
		si->length = length;

	Nlast = div_u64(H + si->length + U - 1, U);
	si->maxdevUnits = Nlast - N;

	si->M = M;
}