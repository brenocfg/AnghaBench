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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int ProtocolRevision (int /*<<< orphan*/ *) ; 
 int ProtocolVersion (int /*<<< orphan*/ *) ; 
 char* ServerVendor (int /*<<< orphan*/ *) ; 
 int VendorRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static void log_x_info(void)
{
	Display *dpy = XOpenDisplay(NULL);
	if (!dpy) {
		blog(LOG_INFO, "Unable to open X display");
		return;
	}

	int protocol_version = ProtocolVersion(dpy);
	int protocol_revision = ProtocolRevision(dpy);
	int vendor_release = VendorRelease(dpy);
	const char *vendor_name = ServerVendor(dpy);

	if (strstr(vendor_name, "X.Org")) {
		blog(LOG_INFO,
		     "Window System: X%d.%d, Vendor: %s, Version: %d"
		     ".%d.%d",
		     protocol_version, protocol_revision, vendor_name,
		     vendor_release / 10000000, (vendor_release / 100000) % 100,
		     (vendor_release / 1000) % 100);
	} else {
		blog(LOG_INFO,
		     "Window System: X%d.%d - vendor string: %s - "
		     "vendor release: %d",
		     protocol_version, protocol_revision, vendor_name,
		     vendor_release);
	}

	XCloseDisplay(dpy);
}