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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ccw1 {scalar_t__ cda; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 scalar_t__ __pa (void*) ; 

__attribute__((used)) static void qeth_setup_ccw(struct ccw1 *ccw, u8 cmd_code, u32 len, void *data)
{
	ccw->cmd_code = cmd_code;
	ccw->flags = CCW_FLAG_SLI;
	ccw->count = len;
	ccw->cda = (__u32) __pa(data);
}