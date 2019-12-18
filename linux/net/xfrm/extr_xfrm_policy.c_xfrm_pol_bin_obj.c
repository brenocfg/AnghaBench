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
struct xfrm_pol_inexact_bin {int /*<<< orphan*/  k; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfrm_pol_bin_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 xfrm_pol_bin_obj(const void *data, u32 len, u32 seed)
{
	const struct xfrm_pol_inexact_bin *b = data;

	return xfrm_pol_bin_key(&b->k, 0, seed);
}