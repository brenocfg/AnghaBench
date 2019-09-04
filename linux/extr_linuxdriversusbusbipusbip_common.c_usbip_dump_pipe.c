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
#define  PIPE_BULK 131 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 unsigned char usb_pipedevice (unsigned int) ; 
 unsigned char usb_pipeendpoint (unsigned int) ; 
 unsigned char usb_pipein (unsigned int) ; 
 unsigned char usb_pipetype (unsigned int) ; 

__attribute__((used)) static void usbip_dump_pipe(unsigned int p)
{
	unsigned char type = usb_pipetype(p);
	unsigned char ep   = usb_pipeendpoint(p);
	unsigned char dev  = usb_pipedevice(p);
	unsigned char dir  = usb_pipein(p);

	pr_debug("dev(%d) ep(%d) [%s] ", dev, ep, dir ? "IN" : "OUT");

	switch (type) {
	case PIPE_ISOCHRONOUS:
		pr_debug("ISO\n");
		break;
	case PIPE_INTERRUPT:
		pr_debug("INT\n");
		break;
	case PIPE_CONTROL:
		pr_debug("CTRL\n");
		break;
	case PIPE_BULK:
		pr_debug("BULK\n");
		break;
	default:
		pr_debug("ERR\n");
		break;
	}
}