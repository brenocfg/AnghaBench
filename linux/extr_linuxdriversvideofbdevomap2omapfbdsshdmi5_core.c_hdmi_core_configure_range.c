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
struct hdmi_core_data {int dummy; } ;
struct csc_table {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 struct csc_table* csc_table_deepcolor ; 
 int /*<<< orphan*/  hdmi_core_csc_config (struct hdmi_core_data*,struct csc_table) ; 

__attribute__((used)) static void hdmi_core_configure_range(struct hdmi_core_data *core)
{
	struct csc_table csc_coeff = { 0 };

	/* support limited range with 24 bit color depth for now */
	csc_coeff = csc_table_deepcolor[0];

	hdmi_core_csc_config(core, csc_coeff);
}