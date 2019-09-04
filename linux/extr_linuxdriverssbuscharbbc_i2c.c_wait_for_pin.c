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
typedef  int u8 ;
struct bbc_i2c_bus {int waiting; int /*<<< orphan*/  wq; scalar_t__ i2c_control_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I2C_PCF_PIN ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_pin(struct bbc_i2c_bus *bp, u8 *status)
{
	DECLARE_WAITQUEUE(wait, current);
	int limit = 32;
	int ret = 1;

	bp->waiting = 1;
	add_wait_queue(&bp->wq, &wait);
	while (limit-- > 0) {
		long val;

		val = wait_event_interruptible_timeout(
				bp->wq,
				(((*status = readb(bp->i2c_control_regs + 0))
				  & I2C_PCF_PIN) == 0),
				msecs_to_jiffies(250));
		if (val > 0) {
			ret = 0;
			break;
		}
	}
	remove_wait_queue(&bp->wq, &wait);
	bp->waiting = 0;

	return ret;
}