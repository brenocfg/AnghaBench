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

/* Variables and functions */
 int /*<<< orphan*/  dev_add_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lowpan_packet_type ; 

void lowpan_rx_init(void)
{
	dev_add_pack(&lowpan_packet_type);
}