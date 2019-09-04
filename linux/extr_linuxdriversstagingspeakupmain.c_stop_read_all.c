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
 int /*<<< orphan*/  cursor_timer ; 
 int /*<<< orphan*/  cursor_track ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prev_cursor_track ; 
 int /*<<< orphan*/  spk_do_flush () ; 
 int spk_shut_up ; 

__attribute__((used)) static void stop_read_all(struct vc_data *vc)
{
	del_timer(&cursor_timer);
	cursor_track = prev_cursor_track;
	spk_shut_up &= 0xfe;
	spk_do_flush();
}