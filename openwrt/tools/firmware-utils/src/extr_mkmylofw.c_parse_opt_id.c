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
struct TYPE_2__ {scalar_t__ rev; scalar_t__ sdid; scalar_t__ did; scalar_t__ svid; scalar_t__ vid; } ;

/* Variables and functions */
 int MAX_ARG_COUNT ; 
 int MAX_ARG_LEN ; 
 int /*<<< orphan*/  dbgmsg (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  errmsg (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ fw_header ; 
 scalar_t__ is_empty_arg (char*) ; 
 int parse_arg (char*,char*,char**) ; 
 scalar_t__ required_arg (char,char*) ; 
 scalar_t__ str2u16 (char*,scalar_t__*) ; 
 scalar_t__ str2u32 (char*,scalar_t__*) ; 

int
parse_opt_id(char ch, char *arg)
{
	char buf[MAX_ARG_LEN];
	char *argv[MAX_ARG_COUNT];
	int argc;
	char *p;

	if (required_arg(ch, arg)) {
		goto err_out;
	}

	argc = parse_arg(arg, buf, argv);

	/* processing vendor ID*/
	p = argv[0];
	if (is_empty_arg(p)) {
		errmsg(0,"vendor id is missing from -%c %s",ch, arg);
		goto err_out;
	} else if (str2u16(p, &fw_header.vid) != 0) {
		errmsg(0,"invalid vendor id: %s", p);
		goto err_out;
	}

	dbgmsg(1, "vendor id is set to 0x%04X", fw_header.vid);

	/* processing device ID*/
	p = argv[1];
	if (is_empty_arg(p)) {
		errmsg(0,"device id is missing from -%c %s",ch, arg);
		goto err_out;
	} else if (str2u16(p, &fw_header.did) != 0) {
		errmsg(0,"invalid device id: %s", p);
		goto err_out;
	}

	dbgmsg(1, "device id is set to 0x%04X", fw_header.did);

	/* processing sub vendor ID*/
	p = argv[2];
	if (is_empty_arg(p)) {
		fw_header.svid = fw_header.vid;
	} else if (str2u16(p, &fw_header.svid) != 0) {
		errmsg(0,"invalid sub vendor id: %s", p);
		goto err_out;
	}

	dbgmsg(1, "sub vendor id is set to 0x%04X", fw_header.svid);

	/* processing device ID*/
	p = argv[3];
	if (is_empty_arg(p)) {
		fw_header.sdid = fw_header.did;
	} else if (str2u16(p, &fw_header.sdid) != 0) {
		errmsg(0,"invalid sub device id: %s", p);
		goto err_out;
	}

	dbgmsg(1, "sub device id is set to 0x%04X", fw_header.sdid);

	/* processing revision */
	p = argv[4];
	if (is_empty_arg(p)) {
		fw_header.rev = 0;
	} else if (str2u32(arg, &fw_header.rev) != 0) {
		errmsg(0,"invalid revision number: %s", p);
		goto err_out;
	}

	dbgmsg(1, "board revision is set to 0x%08X", fw_header.rev);

	return 0;

err_out:
	return -1;
}