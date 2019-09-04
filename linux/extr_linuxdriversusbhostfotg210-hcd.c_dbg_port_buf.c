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
typedef  int u32 ;

/* Variables and functions */
 int PORT_CONNECT ; 
 int PORT_CSC ; 
 int PORT_PE ; 
 int PORT_PEC ; 
 int PORT_RESET ; 
 int PORT_RESUME ; 
 int PORT_SUSPEND ; 
 int /*<<< orphan*/  scnprintf (char*,unsigned int,char*,char const*,char*,int,int,int,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static char *dbg_port_buf(char *buf, unsigned len, const char *label, int port,
		u32 status)
{
	char *sig;

	/* signaling state */
	switch (status & (3 << 10)) {
	case 0 << 10:
		sig = "se0";
		break;
	case 1 << 10:
		sig = "k";
		break; /* low speed */
	case 2 << 10:
		sig = "j";
		break;
	default:
		sig = "?";
		break;
	}

	scnprintf(buf, len, "%s%sport:%d status %06x %d sig=%s%s%s%s%s%s%s%s",
			label, label[0] ? " " : "", port, status,
			status >> 25, /*device address */
			sig,
			(status & PORT_RESET) ? " RESET" : "",
			(status & PORT_SUSPEND) ? " SUSPEND" : "",
			(status & PORT_RESUME) ? " RESUME" : "",
			(status & PORT_PEC) ? " PEC" : "",
			(status & PORT_PE) ? " PE" : "",
			(status & PORT_CSC) ? " CSC" : "",
			(status & PORT_CONNECT) ? " CONNECT" : "");

	return buf;
}