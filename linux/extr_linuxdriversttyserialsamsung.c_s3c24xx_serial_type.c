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
struct uart_port {int type; } ;

/* Variables and functions */
#define  PORT_S3C2410 131 
#define  PORT_S3C2412 130 
#define  PORT_S3C2440 129 
#define  PORT_S3C6400 128 

__attribute__((used)) static const char *s3c24xx_serial_type(struct uart_port *port)
{
	switch (port->type) {
	case PORT_S3C2410:
		return "S3C2410";
	case PORT_S3C2440:
		return "S3C2440";
	case PORT_S3C2412:
		return "S3C2412";
	case PORT_S3C6400:
		return "S3C6400/10";
	default:
		return NULL;
	}
}