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
struct xfs_iext_rec {scalar_t__ hi; } ;

/* Variables and functions */

__attribute__((used)) static bool xfs_iext_rec_is_empty(struct xfs_iext_rec *rec)
{
	return rec->hi == 0;
}