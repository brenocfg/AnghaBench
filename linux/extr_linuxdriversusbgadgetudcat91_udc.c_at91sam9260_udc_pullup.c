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
typedef  int /*<<< orphan*/  u32 ;
struct at91_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_UDP_TXVC ; 
 int /*<<< orphan*/  AT91_UDP_TXVC_PUON ; 
 int /*<<< orphan*/  at91_udp_read (struct at91_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_udp_write (struct at91_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91sam9260_udc_pullup(struct at91_udc *udc, int is_on)
{
	u32 txvc = at91_udp_read(udc, AT91_UDP_TXVC);

	if (is_on)
		txvc |= AT91_UDP_TXVC_PUON;
	else
		txvc &= ~AT91_UDP_TXVC_PUON;

	at91_udp_write(udc, AT91_UDP_TXVC, txvc);
}