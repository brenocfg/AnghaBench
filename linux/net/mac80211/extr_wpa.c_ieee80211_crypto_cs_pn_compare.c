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
typedef  scalar_t__ u8 ;

/* Variables and functions */

__attribute__((used)) static inline int ieee80211_crypto_cs_pn_compare(u8 *pn1, u8 *pn2, int len)
{
	int i;

	/* pn is little endian */
	for (i = len - 1; i >= 0; i--) {
		if (pn1[i] < pn2[i])
			return -1;
		else if (pn1[i] > pn2[i])
			return 1;
	}

	return 0;
}