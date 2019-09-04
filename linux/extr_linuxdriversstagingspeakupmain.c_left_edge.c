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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  say_char (struct vc_data*) ; 
 int spk_parked ; 
 int spk_pos ; 
 int spk_x ; 

__attribute__((used)) static void left_edge(struct vc_data *vc)
{
	spk_parked |= 0x01;
	spk_pos -= spk_x * 2;
	spk_x = 0;
	say_char(vc);
}