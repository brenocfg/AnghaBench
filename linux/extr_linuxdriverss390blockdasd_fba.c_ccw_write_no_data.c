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
struct ccw1 {scalar_t__ count; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DASD_FBA_CCW_WRITE ; 

__attribute__((used)) static void ccw_write_no_data(struct ccw1 *ccw)
{
	ccw->cmd_code = DASD_FBA_CCW_WRITE;
	ccw->flags |= CCW_FLAG_SLI;
	ccw->count = 0;
}