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
struct TCP_ConnectionTable {TYPE_1__* banner1; } ;
struct TYPE_2__ {unsigned int is_capture_cert; unsigned int is_capture_html; unsigned int is_capture_heartbleed; unsigned int is_capture_ticketbleed; } ;

/* Variables and functions */

void
tcpcon_set_banner_flags(struct TCP_ConnectionTable *tcpcon,
    unsigned is_capture_cert,
    unsigned is_capture_html,
    unsigned is_capture_heartbleed,
	unsigned is_capture_ticketbleed)
{
    tcpcon->banner1->is_capture_cert = is_capture_cert;
    tcpcon->banner1->is_capture_html = is_capture_html;
    tcpcon->banner1->is_capture_heartbleed = is_capture_heartbleed;
    tcpcon->banner1->is_capture_ticketbleed = is_capture_ticketbleed;
}