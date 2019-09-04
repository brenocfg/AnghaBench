#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ spectral_bin_discard; } ;
struct ath10k {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_power_of_2 (size_t) ; 

__attribute__((used)) static inline size_t ath10k_spectral_fix_bin_size(struct ath10k *ar,
						  size_t bin_len)
{
	/* some chipsets reports bin size as 2^n bytes + 'm' bytes in
	 * report mode 2. First 2^n bytes carries inband tones and last
	 * 'm' bytes carries band edge detection data mainly used in
	 * radar detection purpose. Strip last 'm' bytes to make bin size
	 * as a valid one. 'm' can take possible values of 4, 12.
	 */
	if (!is_power_of_2(bin_len))
		bin_len -= ar->hw_params.spectral_bin_discard;

	return bin_len;
}