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
struct snd_pcxhr {unsigned char* aes_bits; int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_OUTPB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char PCXHR_SUER_BIT_C_WRITE_MASK ; 
 int /*<<< orphan*/  PCXHR_XLX_CSUER ; 
 int /*<<< orphan*/  PCXHR_XLX_RUER ; 

int hr222_iec958_update_byte(struct snd_pcxhr *chip,
			     int aes_idx, unsigned char aes_bits)
{
	int i;
	unsigned char new_bits = aes_bits;
	unsigned char old_bits = chip->aes_bits[aes_idx];
	unsigned char idx = (unsigned char)(aes_idx * 8);
	for (i = 0; i < 8; i++) {
		if ((old_bits & 0x01) != (new_bits & 0x01)) {
			/* idx < 192 */
			PCXHR_OUTPB(chip->mgr, PCXHR_XLX_RUER, idx);
			/* write C and U bit */
			PCXHR_OUTPB(chip->mgr, PCXHR_XLX_CSUER, new_bits&0x01 ?
				    PCXHR_SUER_BIT_C_WRITE_MASK : 0);
		}
		idx++;
		old_bits >>= 1;
		new_bits >>= 1;
	}
	chip->aes_bits[aes_idx] = aes_bits;
	return 0;
}