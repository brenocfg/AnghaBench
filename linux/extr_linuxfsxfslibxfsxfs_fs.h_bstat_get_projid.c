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
typedef  int uint32_t ;
struct xfs_bstat {int bs_projid_lo; scalar_t__ bs_projid_hi; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
bstat_get_projid(struct xfs_bstat *bs)
{
	return (uint32_t)bs->bs_projid_hi << 16 | bs->bs_projid_lo;
}