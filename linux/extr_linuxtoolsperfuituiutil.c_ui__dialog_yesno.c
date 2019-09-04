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

/* Variables and functions */
 int ui__question_window (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

int ui__dialog_yesno(const char *msg)
{
	return ui__question_window(NULL, msg, "Enter: Yes, ESC: No", 0);
}