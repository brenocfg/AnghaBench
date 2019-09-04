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
struct uart_port {int dummy; } ;
struct dz_port {int /*<<< orphan*/  cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DZ_LPR ; 
 int /*<<< orphan*/  DZ_RXENAB ; 
 int /*<<< orphan*/  dz_out (struct dz_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_stop_rx(struct uart_port *uport)
{
	struct dz_port *dport = to_dport(uport);

	dport->cflag &= ~DZ_RXENAB;
	dz_out(dport, DZ_LPR, dport->cflag);
}