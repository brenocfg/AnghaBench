#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_iext_rec {int dummy; } ;
struct xfs_iext_cursor {size_t pos; TYPE_1__* leaf; } ;
struct TYPE_2__ {struct xfs_iext_rec* recs; } ;

/* Variables and functions */

__attribute__((used)) static inline struct xfs_iext_rec *cur_rec(struct xfs_iext_cursor *cur)
{
	return &cur->leaf->recs[cur->pos];
}