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
typedef  int /*<<< orphan*/  u_short ;
struct vc_data {scalar_t__ vc_pos; int /*<<< orphan*/  vc_y; int /*<<< orphan*/  vc_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_attributes (struct vc_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spk_attr ; 
 scalar_t__ spk_cp ; 
 int /*<<< orphan*/  spk_cx ; 
 int /*<<< orphan*/  spk_cy ; 
 int /*<<< orphan*/  spk_old_attr ; 
 scalar_t__ spk_pos ; 
 int /*<<< orphan*/  spk_x ; 
 int /*<<< orphan*/  spk_y ; 

__attribute__((used)) static void speakup_date(struct vc_data *vc)
{
	spk_x = spk_cx = vc->vc_x;
	spk_y = spk_cy = vc->vc_y;
	spk_pos = spk_cp = vc->vc_pos;
	spk_old_attr = spk_attr;
	spk_attr = get_attributes(vc, (u_short *)spk_pos);
}