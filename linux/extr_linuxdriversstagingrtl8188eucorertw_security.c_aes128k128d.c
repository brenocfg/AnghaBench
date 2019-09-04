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
 int /*<<< orphan*/  byte_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mix_column (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shift_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xor_128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aes128k128d(u8 *key, u8 *data, u8 *ciphertext)
{
	int round;
	int i;
	u8 intermediatea[16];
	u8 intermediateb[16];
	u8 round_key[16];

	for (i = 0; i < 16; i++)
		round_key[i] = key[i];
	for (round = 0; round < 11; round++) {
		if (round == 0) {
			xor_128(round_key, data, ciphertext);
			next_key(round_key, round);
		} else if (round == 10) {
			byte_sub(ciphertext, intermediatea);
			shift_row(intermediatea, intermediateb);
			xor_128(intermediateb, round_key, ciphertext);
		} else {    /* 1 - 9 */
			byte_sub(ciphertext, intermediatea);
			shift_row(intermediatea, intermediateb);
			mix_column(&intermediateb[0], &intermediatea[0]);
			mix_column(&intermediateb[4], &intermediatea[4]);
			mix_column(&intermediateb[8], &intermediatea[8]);
			mix_column(&intermediateb[12], &intermediatea[12]);
			xor_128(intermediatea, round_key, ciphertext);
			next_key(round_key, round);
		}
	}
}