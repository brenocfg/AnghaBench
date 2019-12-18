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
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 int AZX_INT_CTRL_EN ; 
 int AZX_INT_GLOBAL_EN ; 
 int /*<<< orphan*/  INTCTL ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void azx_int_enable(struct hdac_bus *bus)
{
	/* enable controller CIE and GIE */
	snd_hdac_chip_updatel(bus, INTCTL,
			      AZX_INT_CTRL_EN | AZX_INT_GLOBAL_EN,
			      AZX_INT_CTRL_EN | AZX_INT_GLOBAL_EN);
}