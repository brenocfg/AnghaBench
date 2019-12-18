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
struct idr {int /*<<< orphan*/  idr_rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDR_FREE ; 
 scalar_t__ radix_tree_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ radix_tree_tagged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool idr_is_empty(const struct idr *idr)
{
	return radix_tree_empty(&idr->idr_rt) &&
		radix_tree_tagged(&idr->idr_rt, IDR_FREE);
}