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
struct parport {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* read_status ) (struct parport*) ;} ;

/* Variables and functions */
 int PARPORT_STATUS_ACK ; 
 int stub1 (struct parport*) ; 

__attribute__((used)) static inline int signal_is_set(struct parport *port)
{
	return (port->ops->read_status(port) & PARPORT_STATUS_ACK) != 0;
}