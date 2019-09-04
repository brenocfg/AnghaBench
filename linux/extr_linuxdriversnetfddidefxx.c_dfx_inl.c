#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ port; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  inl (scalar_t__) ; 

__attribute__((used)) static inline void dfx_inl(DFX_board_t *bp, int offset, u32 *data)
{
	*data = inl(bp->base.port + offset);
}