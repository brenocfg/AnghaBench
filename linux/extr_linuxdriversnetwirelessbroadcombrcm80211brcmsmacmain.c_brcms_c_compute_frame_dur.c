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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct brcms_c_info {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 scalar_t__ brcms_c_calc_ack_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ brcms_c_calc_frame_time (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int get_sifs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16
brcms_c_compute_frame_dur(struct brcms_c_info *wlc, u32 rate,
		      u8 preamble_type, uint next_frag_len)
{
	u16 dur, sifs;

	sifs = get_sifs(wlc->band);

	dur = sifs;
	dur += (u16) brcms_c_calc_ack_time(wlc, rate, preamble_type);

	if (next_frag_len) {
		/* Double the current DUR to get 2 SIFS + 2 ACKs */
		dur *= 2;
		/* add another SIFS and the frag time */
		dur += sifs;
		dur +=
		    (u16) brcms_c_calc_frame_time(wlc, rate, preamble_type,
						 next_frag_len);
	}
	return dur;
}