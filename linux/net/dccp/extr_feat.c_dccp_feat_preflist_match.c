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
typedef  size_t u8 ;

/* Variables and functions */

__attribute__((used)) static int dccp_feat_preflist_match(u8 *servlist, u8 slen, u8 *clilist, u8 clen)
{
	u8 c, s;

	for (s = 0; s < slen; s++)
		for (c = 0; c < clen; c++)
			if (servlist[s] == clilist[c])
				return servlist[s];
	return -1;
}