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
struct ccw1 {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DASD_FBA_CCW_WRITE ; 
 int /*<<< orphan*/  ZERO_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ page_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccw_write_zero(struct ccw1 *ccw, int count)
{
	ccw->cmd_code = DASD_FBA_CCW_WRITE;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = count;
	ccw->cda = (__u32) (addr_t) page_to_phys(ZERO_PAGE(0));
}