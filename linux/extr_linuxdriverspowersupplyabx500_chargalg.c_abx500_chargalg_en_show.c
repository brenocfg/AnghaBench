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
struct TYPE_2__ {scalar_t__ usb_suspended; scalar_t__ ac_suspended; } ;
struct abx500_chargalg {TYPE_1__ susp_status; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t abx500_chargalg_en_show(struct abx500_chargalg *di,
				       char *buf)
{
	return sprintf(buf, "%d\n",
		       di->susp_status.ac_suspended &&
		       di->susp_status.usb_suspended);
}