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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ GAIN_AUGMENT ; 
 scalar_t__ SIDETONE_BASE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ nau8825_intlog10_dec3 (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 nau8825_xtalk_sidetone(u32 sig_org, u32 sig_cros)
{
	u32 gain, sidetone;

	if (unlikely(sig_org == 0) || unlikely(sig_cros == 0)) {
		WARN_ON(1);
		return 0;
	}

	sig_org = nau8825_intlog10_dec3(sig_org);
	sig_cros = nau8825_intlog10_dec3(sig_cros);
	if (sig_org >= sig_cros)
		gain = (sig_org - sig_cros) * 20 + GAIN_AUGMENT;
	else
		gain = (sig_cros - sig_org) * 20 + GAIN_AUGMENT;
	sidetone = SIDETONE_BASE - gain * 2;
	sidetone /= 1000;

	return sidetone;
}