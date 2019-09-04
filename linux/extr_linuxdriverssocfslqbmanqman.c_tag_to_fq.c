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
typedef  scalar_t__ u32 ;
struct qman_fq {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct qman_fq *tag_to_fq(u32 tag)
{
#if BITS_PER_LONG == 64
	return idx_to_fq(tag);
#else
	return (struct qman_fq *)tag;
#endif
}