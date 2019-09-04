#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  xtnt_blk; int /*<<< orphan*/  xtnt_size; } ;
typedef  TYPE_1__ qnx4_xtnt_t ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 try_extent(qnx4_xtnt_t *extent, u32 *offset)
{
	u32 size = le32_to_cpu(extent->xtnt_size);
	if (*offset < size)
		return le32_to_cpu(extent->xtnt_blk) + *offset - 1;
	*offset -= size;
	return 0;
}