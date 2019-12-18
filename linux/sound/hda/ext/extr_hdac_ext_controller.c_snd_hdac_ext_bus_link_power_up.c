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
struct hdac_ext_link {int /*<<< orphan*/  ml_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_MLCTL_SPA ; 
 int /*<<< orphan*/  AZX_REG_ML_LCTL ; 
 int check_hdac_link_power_active (struct hdac_ext_link*,int) ; 
 int /*<<< orphan*/  snd_hdac_updatel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_hdac_ext_bus_link_power_up(struct hdac_ext_link *link)
{
	snd_hdac_updatel(link->ml_addr, AZX_REG_ML_LCTL,
			 AZX_MLCTL_SPA, AZX_MLCTL_SPA);

	return check_hdac_link_power_active(link, true);
}