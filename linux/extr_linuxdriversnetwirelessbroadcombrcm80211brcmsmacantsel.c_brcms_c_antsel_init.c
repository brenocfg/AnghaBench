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
struct antsel_info {scalar_t__ antsel_type; int /*<<< orphan*/  antcfg_11n; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 scalar_t__ ANTSEL_2x4 ; 
 int /*<<< orphan*/  brcms_c_antsel_cfgupd (struct antsel_info*,int /*<<< orphan*/ *) ; 

void brcms_c_antsel_init(struct antsel_info *asi)
{
	if ((asi->antsel_type == ANTSEL_2x3) ||
	    (asi->antsel_type == ANTSEL_2x4))
		brcms_c_antsel_cfgupd(asi, &asi->antcfg_11n);
}