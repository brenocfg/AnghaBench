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
typedef  scalar_t__ u8 ;
struct fsg_dev {scalar_t__ config; TYPE_1__* gadget; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  INFO (struct fsg_dev*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int do_set_interface (struct fsg_dev*,int) ; 
 int /*<<< orphan*/  usb_speed_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_set_config(struct fsg_dev *fsg, u8 new_config)
{
	int	rc = 0;

	/* Disable the single interface */
	if (fsg->config != 0) {
		DBG(fsg, "reset config\n");
		fsg->config = 0;
		rc = do_set_interface(fsg, -1);
	}

	/* Enable the interface */
	if (new_config != 0) {
		fsg->config = new_config;
		if ((rc = do_set_interface(fsg, 0)) != 0)
			fsg->config = 0;	// Reset on errors
		else
			INFO(fsg, "%s config #%d\n",
			     usb_speed_string(fsg->gadget->speed),
			     fsg->config);
	}
	return rc;
}