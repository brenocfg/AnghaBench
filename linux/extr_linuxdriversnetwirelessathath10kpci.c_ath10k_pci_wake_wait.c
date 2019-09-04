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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PCIE_WAKE_LATE_US ; 
 int PCIE_WAKE_TIMEOUT ; 
 scalar_t__ ath10k_pci_is_awake (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ath10k_pci_wake_wait(struct ath10k *ar)
{
	int tot_delay = 0;
	int curr_delay = 5;

	while (tot_delay < PCIE_WAKE_TIMEOUT) {
		if (ath10k_pci_is_awake(ar)) {
			if (tot_delay > PCIE_WAKE_LATE_US)
				ath10k_warn(ar, "device wakeup took %d ms which is unusually long, otherwise it works normally.\n",
					    tot_delay / 1000);
			return 0;
		}

		udelay(curr_delay);
		tot_delay += curr_delay;

		if (curr_delay < 50)
			curr_delay += 5;
	}

	return -ETIMEDOUT;
}