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
struct metapath {struct buffer_head** mp_bh; } ;
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */

__attribute__((used)) static inline const __be64 *metaend(unsigned int height, const struct metapath *mp)
{
	const struct buffer_head *bh = mp->mp_bh[height];
	return (const __be64 *)(bh->b_data + bh->b_size);
}