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
typedef  int u8 ;

/* Variables and functions */
 int const WLAN_EID_FRAGMENT ; 

__attribute__((used)) static size_t skip_ie(const u8 *ies, size_t ielen, size_t pos)
{
	/* we assume a validly formed IEs buffer */
	u8 len = ies[pos + 1];

	pos += 2 + len;

	/* the IE itself must have 255 bytes for fragments to follow */
	if (len < 255)
		return pos;

	while (pos < ielen && ies[pos] == WLAN_EID_FRAGMENT) {
		len = ies[pos + 1];
		pos += 2 + len;
	}

	return pos;
}