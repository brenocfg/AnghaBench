#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct maven_data {struct matrox_fb_info* primary_head; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct matrox_fb_info {TYPE_2__ altout; TYPE_1__* outputs; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/ * data; int /*<<< orphan*/ * output; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  MATROXFB_OUTPUT_MODE_MONITOR ; 
 int /*<<< orphan*/  MATROXFB_SRC_NONE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct maven_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int maven_shutdown_client(struct i2c_client* clnt) {
	struct maven_data* md = i2c_get_clientdata(clnt);

	if (md->primary_head) {
		struct matrox_fb_info *minfo = md->primary_head;

		down_write(&minfo->altout.lock);
		minfo->outputs[1].src = MATROXFB_SRC_NONE;
		minfo->outputs[1].output = NULL;
		minfo->outputs[1].data = NULL;
		minfo->outputs[1].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		up_write(&minfo->altout.lock);
		md->primary_head = NULL;
	}
	return 0;
}