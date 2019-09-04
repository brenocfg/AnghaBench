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
struct vc_data {int /*<<< orphan*/  vc_num; } ;
struct console_font {int dummy; } ;

/* Variables and functions */
 int newport_set_font (int /*<<< orphan*/ ,struct console_font*) ; 

__attribute__((used)) static int newport_font_set(struct vc_data *vc, struct console_font *font, unsigned flags)
{
	return newport_set_font(vc->vc_num, font);
}