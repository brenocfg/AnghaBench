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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIDS_FILE ; 
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int list_devices (int) ; 
 int list_exported_devices (int /*<<< orphan*/ ) ; 
 int list_gadget_devices (int) ; 
#define  no_argument 129 
 int /*<<< orphan*/  optarg ; 
#define  required_argument 128 
 int /*<<< orphan*/  usbip_list_usage () ; 
 int /*<<< orphan*/  usbip_names_free () ; 
 scalar_t__ usbip_names_init (int /*<<< orphan*/ ) ; 

int usbip_list(int argc, char *argv[])
{
	static const struct option opts[] = {
		{ "parsable", no_argument,       NULL, 'p' },
		{ "remote",   required_argument, NULL, 'r' },
		{ "local",    no_argument,       NULL, 'l' },
		{ "device",    no_argument,       NULL, 'd' },
		{ NULL,       0,                 NULL,  0  }
	};

	bool parsable = false;
	int opt;
	int ret = -1;

	if (usbip_names_init(USBIDS_FILE))
		err("failed to open %s", USBIDS_FILE);

	for (;;) {
		opt = getopt_long(argc, argv, "pr:ld", opts, NULL);

		if (opt == -1)
			break;

		switch (opt) {
		case 'p':
			parsable = true;
			break;
		case 'r':
			ret = list_exported_devices(optarg);
			goto out;
		case 'l':
			ret = list_devices(parsable);
			goto out;
		case 'd':
			ret = list_gadget_devices(parsable);
			goto out;
		default:
			goto err_out;
		}
	}

err_out:
	usbip_list_usage();
out:
	usbip_names_free();

	return ret;
}