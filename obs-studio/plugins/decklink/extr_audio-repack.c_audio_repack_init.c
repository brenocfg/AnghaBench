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
typedef  int uint8_t ;
struct audio_repack {int base_src_size; int base_dst_size; int extra_dst_size; int /*<<< orphan*/ * repack_func; } ;
typedef  size_t audio_repack_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct audio_repack*,int /*<<< orphan*/ ,int) ; 
 size_t repack_mode_8ch_swap ; 
 size_t repack_mode_8to5ch_swap ; 
 size_t repack_mode_8to6ch_swap ; 
 int /*<<< orphan*/  repack_squash ; 
 int /*<<< orphan*/  repack_squash_swap ; 

int audio_repack_init(struct audio_repack *repack,
		      audio_repack_mode_t repack_mode, uint8_t sample_bit)
{
	memset(repack, 0, sizeof(*repack));

	if (sample_bit != 16)
		return -1;
	int _audio_repack_ch[8] = {3, 4, 5, 6, 5, 6, 8, 8};
	repack->base_src_size = 8 * (16 / 8);
	repack->base_dst_size = _audio_repack_ch[repack_mode] * (16 / 8);
	repack->extra_dst_size = 8 - _audio_repack_ch[repack_mode];
	repack->repack_func = &repack_squash;
	if (repack_mode == repack_mode_8to5ch_swap ||
	    repack_mode == repack_mode_8to6ch_swap ||
	    repack_mode == repack_mode_8ch_swap)
		repack->repack_func = &repack_squash_swap;

	return 0;
}