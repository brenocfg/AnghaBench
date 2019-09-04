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
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_flush_wq ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _dasd_wake_block_flush_cb(struct dasd_ccw_req *cqr, void *data)
{
	wake_up(&dasd_flush_wq);
}