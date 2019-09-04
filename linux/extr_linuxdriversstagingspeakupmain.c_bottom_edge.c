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
struct vc_data {int vc_rows; int vc_size_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  say_line (struct vc_data*) ; 
 int spk_parked ; 
 int spk_pos ; 
 int spk_y ; 

__attribute__((used)) static void bottom_edge(struct vc_data *vc)
{
	spk_parked |= 0x01;
	spk_pos += (vc->vc_rows - spk_y - 1) * vc->vc_size_row;
	spk_y = vc->vc_rows - 1;
	say_line(vc);
}