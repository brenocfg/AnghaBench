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
struct uart_port {int dummy; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ PORT_S3C6400 ; 
 TYPE_2__* to_ourport (struct uart_port*) ; 

__attribute__((used)) static int s3c24xx_serial_has_interrupt_mask(struct uart_port *port)
{
	return to_ourport(port)->info->type == PORT_S3C6400;
}