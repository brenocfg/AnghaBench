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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static void wm_adsp_remove_padding(u32 *buf, int nwords, int data_word_size)
{
	u8 *pack_in = (u8 *)buf;
	u8 *pack_out = (u8 *)buf;
	int i, j;

	/* Remove the padding bytes from the data read from the DSP */
	for (i = 0; i < nwords; i++) {
		for (j = 0; j < data_word_size; j++)
			*pack_out++ = *pack_in++;

		pack_in += sizeof(*buf) - data_word_size;
	}
}