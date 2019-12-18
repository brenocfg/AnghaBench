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
struct switch_port_stats {int dummy; } ;
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8367B_MIB_RXB_ID ; 
 int /*<<< orphan*/  RTL8367B_MIB_TXB_ID ; 
 int rtl8366_sw_get_port_stats (struct switch_dev*,int,struct switch_port_stats*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8367b_sw_get_port_stats(struct switch_dev *dev, int port,
                                        struct switch_port_stats *stats)
{
	return (rtl8366_sw_get_port_stats(dev, port, stats,
				RTL8367B_MIB_TXB_ID, RTL8367B_MIB_RXB_ID));
}