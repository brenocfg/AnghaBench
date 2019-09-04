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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
ath_cmn_copy_fft_frame(u8 *in, u8 *out, int sample_len, int sample_bytes)
{
	switch (sample_bytes - sample_len) {
	case -1:
		/* First byte missing */
		memcpy(&out[1], in,
		       sample_len - 1);
		break;
	case 0:
		/* Length correct, nothing to do. */
		memcpy(out, in, sample_len);
		break;
	case 1:
		/* MAC added 2 extra bytes AND first byte
		 * is missing.
		 */
		memcpy(&out[1], in, 30);
		out[31] = in[31];
		memcpy(&out[32], &in[33],
		       sample_len - 32);
		break;
	case 2:
		/* MAC added 2 extra bytes at bin 30 and 32,
		 * remove them.
		 */
		memcpy(out, in, 30);
		out[30] = in[31];
		memcpy(&out[31], &in[33],
		       sample_len - 31);
		break;
	default:
		break;
	}
}