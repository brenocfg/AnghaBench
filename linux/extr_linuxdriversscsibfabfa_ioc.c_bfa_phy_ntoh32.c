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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_phy_ntoh32(u32 *obuf, u32 *ibuf, int sz)
{
	int i, m = sz >> 2;

	for (i = 0; i < m; i++)
		obuf[i] = be32_to_cpu(ibuf[i]);
}