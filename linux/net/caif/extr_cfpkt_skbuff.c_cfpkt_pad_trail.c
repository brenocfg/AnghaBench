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
typedef  int /*<<< orphan*/  u16 ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int cfpkt_add_body (struct cfpkt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cfpkt_pad_trail(struct cfpkt *pkt, u16 len)
{
	return cfpkt_add_body(pkt, NULL, len);
}