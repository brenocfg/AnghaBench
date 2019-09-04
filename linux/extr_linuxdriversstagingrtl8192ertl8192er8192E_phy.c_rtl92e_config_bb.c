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
struct net_device {int dummy; } ;

/* Variables and functions */
 int _rtl92e_bb_config_para_file (struct net_device*) ; 
 int /*<<< orphan*/  _rtl92e_init_bb_rf_reg_def (struct net_device*) ; 

bool rtl92e_config_bb(struct net_device *dev)
{
	_rtl92e_init_bb_rf_reg_def(dev);
	return _rtl92e_bb_config_para_file(dev);
}