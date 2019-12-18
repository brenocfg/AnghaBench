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
struct xfs_refcount_irec {scalar_t__ rc_startblock; } ;

/* Variables and functions */
 scalar_t__ NULLAGBLOCK ; 

__attribute__((used)) static inline bool
xfs_refc_valid(
	struct xfs_refcount_irec	*rc)
{
	return rc->rc_startblock != NULLAGBLOCK;
}