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
struct uart_pmac_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZS_IS_INTMODEM (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_IRDA (struct uart_pmac_port*) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 

__attribute__((used)) static const char *pmz_type(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);

	if (ZS_IS_IRDA(uap))
		return "Z85c30 ESCC - Infrared port";
	else if (ZS_IS_INTMODEM(uap))
		return "Z85c30 ESCC - Internal modem";
	return "Z85c30 ESCC - Serial port";
}