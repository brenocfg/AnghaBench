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
struct idr {int idr_base; scalar_t__ idr_next; int /*<<< orphan*/  idr_rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDR_RT_MARKER ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void idr_init_base(struct idr *idr, int base)
{
	INIT_RADIX_TREE(&idr->idr_rt, IDR_RT_MARKER);
	idr->idr_base = base;
	idr->idr_next = 0;
}