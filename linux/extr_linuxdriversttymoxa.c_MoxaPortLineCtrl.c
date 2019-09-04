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
typedef  int /*<<< orphan*/  u8 ;
struct moxa_port {int /*<<< orphan*/  tableAddr; int /*<<< orphan*/  lineCtrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTR_ON ; 
 int /*<<< orphan*/  FC_LineControl ; 
 int /*<<< orphan*/  RTS_ON ; 
 int /*<<< orphan*/  moxafunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MoxaPortLineCtrl(struct moxa_port *port, int dtr, int rts)
{
	u8 mode = 0;

	if (dtr)
		mode |= DTR_ON;
	if (rts)
		mode |= RTS_ON;
	port->lineCtrl = mode;
	moxafunc(port->tableAddr, FC_LineControl, mode);
}