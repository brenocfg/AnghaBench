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
struct vc_data {int /*<<< orphan*/  vc_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  say_screen_from_to (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spk_y ; 

__attribute__((used)) static void say_to_bottom(struct vc_data *vc)
{
	say_screen_from_to(vc, spk_y, vc->vc_rows);
}