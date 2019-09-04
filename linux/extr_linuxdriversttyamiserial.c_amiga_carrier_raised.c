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
struct tty_port {int dummy; } ;
struct TYPE_2__ {int pra; } ;

/* Variables and functions */
 int SER_DCD ; 
 TYPE_1__ ciab ; 

__attribute__((used)) static int amiga_carrier_raised(struct tty_port *port)
{
	return !(ciab.pra & SER_DCD);
}