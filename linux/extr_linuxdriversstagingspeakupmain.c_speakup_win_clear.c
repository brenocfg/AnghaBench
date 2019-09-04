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
 int /*<<< orphan*/  MSG_WINDOW_CLEARED ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ win_bottom ; 
 scalar_t__ win_left ; 
 scalar_t__ win_right ; 
 scalar_t__ win_start ; 
 scalar_t__ win_top ; 

__attribute__((used)) static void speakup_win_clear(struct vc_data *vc)
{
	win_top = 0;
	win_bottom = 0;
	win_left = 0;
	win_right = 0;
	win_start = 0;
	synth_printf("%s\n", spk_msg_get(MSG_WINDOW_CLEARED));
}