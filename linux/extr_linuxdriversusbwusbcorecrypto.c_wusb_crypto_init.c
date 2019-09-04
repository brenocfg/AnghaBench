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

/* Variables and functions */
 scalar_t__ debug_crypto_verify ; 
 int wusb_key_derive_verify () ; 
 int wusb_oob_mic_verify () ; 

int wusb_crypto_init(void)
{
	int result;

	if (debug_crypto_verify) {
		result = wusb_key_derive_verify();
		if (result < 0)
			return result;
		return wusb_oob_mic_verify();
	}
	return 0;
}