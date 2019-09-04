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
struct wiphy {int n_cipher_suites; scalar_t__* cipher_suites; } ;

/* Variables and functions */

bool cfg80211_supported_cipher_suite(struct wiphy *wiphy, u32 cipher)
{
	int i;
	for (i = 0; i < wiphy->n_cipher_suites; i++)
		if (cipher == wiphy->cipher_suites[i])
			return true;
	return false;
}