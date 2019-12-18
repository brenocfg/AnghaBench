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

/* Variables and functions */
 unsigned long UINT16_MAX ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  err (char*,char*,...) ; 
 int /*<<< orphan*/  info (char*,unsigned long,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 unsigned long usbip_port ; 
 char* usbip_port_string ; 

void usbip_setup_port_number(char *arg)
{
	dbg("parsing port arg '%s'", arg);
	char *end;
	unsigned long int port = strtoul(arg, &end, 10);

	if (end == arg) {
		err("port: could not parse '%s' as a decimal integer", arg);
		return;
	}

	if (*end != '\0') {
		err("port: garbage at end of '%s'", arg);
		return;
	}

	if (port > UINT16_MAX) {
		err("port: %s too high (max=%d)",
		    arg, UINT16_MAX);
		return;
	}

	usbip_port = port;
	usbip_port_string = arg;
	info("using port %d (\"%s\")", usbip_port, usbip_port_string);
}