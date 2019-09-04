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
struct lynx_accel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONTROL ; 
 unsigned int DE_CONTROL_TRANSPARENCY ; 
 unsigned int DE_CONTROL_TRANSPARENCY_MATCH ; 
 unsigned int DE_CONTROL_TRANSPARENCY_SELECT ; 
 unsigned int read_dpr (struct lynx_accel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int deGetTransparency(struct lynx_accel *accel)
{
	unsigned int de_ctrl;

	de_ctrl = read_dpr(accel, DE_CONTROL);

	de_ctrl &= (DE_CONTROL_TRANSPARENCY_MATCH |
		    DE_CONTROL_TRANSPARENCY_SELECT | DE_CONTROL_TRANSPARENCY);

	return de_ctrl;
}