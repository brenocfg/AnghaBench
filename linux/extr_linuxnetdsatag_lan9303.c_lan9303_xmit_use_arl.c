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
typedef  int /*<<< orphan*/  u8 ;
struct lan9303 {scalar_t__ is_bridged; } ;
struct dsa_port {TYPE_1__* ds; } ;
struct TYPE_2__ {struct lan9303* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan9303_xmit_use_arl(struct dsa_port *dp, u8 *dest_addr)
{
	struct lan9303 *chip = dp->ds->priv;

	return chip->is_bridged && !is_multicast_ether_addr(dest_addr);
}