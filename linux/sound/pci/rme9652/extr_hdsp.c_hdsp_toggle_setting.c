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
typedef  int u32 ;
struct hdsp {int control_register; } ;

/* Variables and functions */

__attribute__((used)) static int hdsp_toggle_setting(struct hdsp *hdsp, u32 regmask)
{
	return (hdsp->control_register & regmask) ? 1 : 0;
}