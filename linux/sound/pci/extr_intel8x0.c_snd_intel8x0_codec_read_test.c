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
struct intel8x0 {unsigned int codec_ready_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOB_STA ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_GSCI ; 
 unsigned int ICH_RCS ; 
 int /*<<< orphan*/  iagetword (struct intel8x0*,unsigned int) ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ snd_intel8x0_codec_semaphore (struct intel8x0*,unsigned int) ; 

__attribute__((used)) static void snd_intel8x0_codec_read_test(struct intel8x0 *chip,
					 unsigned int codec)
{
	unsigned int tmp;

	if (snd_intel8x0_codec_semaphore(chip, codec) >= 0) {
		iagetword(chip, codec * 0x80);
		if ((tmp = igetdword(chip, ICHREG(GLOB_STA))) & ICH_RCS) {
			/* reset RCS and preserve other R/WC bits */
			iputdword(chip, ICHREG(GLOB_STA), tmp &
				  ~(chip->codec_ready_bits | ICH_GSCI));
		}
	}
}