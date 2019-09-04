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
struct qman_fq {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 fq_to_tag(struct qman_fq *fq)
{
#if BITS_PER_LONG == 64
	return fq->idx;
#else
	return (u32)fq;
#endif
}