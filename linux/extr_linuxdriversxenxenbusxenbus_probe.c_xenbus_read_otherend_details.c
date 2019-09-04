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
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  otherend; int /*<<< orphan*/  otherend_id; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  free_otherend_details (struct xenbus_device*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int xenbus_gather (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int xenbus_read_otherend_details(struct xenbus_device *xendev,
				 char *id_node, char *path_node)
{
	int err = xenbus_gather(XBT_NIL, xendev->nodename,
				id_node, "%i", &xendev->otherend_id,
				path_node, NULL, &xendev->otherend,
				NULL);
	if (err) {
		xenbus_dev_fatal(xendev, err,
				 "reading other end details from %s",
				 xendev->nodename);
		return err;
	}
	if (strlen(xendev->otherend) == 0 ||
	    !xenbus_exists(XBT_NIL, xendev->otherend, "")) {
		xenbus_dev_fatal(xendev, -ENOENT,
				 "unable to read other end from %s.  "
				 "missing or inaccessible.",
				 xendev->nodename);
		free_otherend_details(xendev);
		return -ENOENT;
	}

	return 0;
}