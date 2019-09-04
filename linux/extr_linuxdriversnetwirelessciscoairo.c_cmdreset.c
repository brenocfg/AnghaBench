#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct airo_info {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SOFTRESET ; 
 int /*<<< orphan*/  COMMAND ; 
 int EBUSY ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  airo_print_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  waitbusy (struct airo_info*) ; 

__attribute__((used)) static int cmdreset(struct airo_info *ai) {
	disable_MAC(ai, 1);

	if(!waitbusy (ai)){
		airo_print_info(ai->dev->name, "Waitbusy hang before RESET");
		return -EBUSY;
	}

	OUT4500(ai,COMMAND,CMD_SOFTRESET);

	ssleep(1);			/* WAS 600 12/7/00 */

	if(!waitbusy (ai)){
		airo_print_info(ai->dev->name, "Waitbusy hang AFTER RESET");
		return -EBUSY;
	}
	return 0;
}