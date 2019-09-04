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
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int ath6kl_bmi_lz_data (struct ath6kl*,int /*<<< orphan*/ *,int) ; 
 int ath6kl_bmi_lz_stream_start (struct ath6kl*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

int ath6kl_bmi_fast_download(struct ath6kl *ar, u32 addr, u8 *buf, u32 len)
{
	int ret;
	u32 last_word = 0;
	u32 last_word_offset = len & ~0x3;
	u32 unaligned_bytes = len & 0x3;

	ret = ath6kl_bmi_lz_stream_start(ar, addr);
	if (ret)
		return ret;

	if (unaligned_bytes) {
		/* copy the last word into a zero padded buffer */
		memcpy(&last_word, &buf[last_word_offset], unaligned_bytes);
	}

	ret = ath6kl_bmi_lz_data(ar, buf, last_word_offset);
	if (ret)
		return ret;

	if (unaligned_bytes)
		ret = ath6kl_bmi_lz_data(ar, (u8 *)&last_word, 4);

	if (!ret) {
		/* Close compressed stream and open a new (fake) one.
		 * This serves mainly to flush Target caches. */
		ret = ath6kl_bmi_lz_stream_start(ar, 0x00);
	}
	return ret;
}