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
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ save_and_exit ; 
 int /*<<< orphan*/  show_textbox (int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  silent ; 

__attribute__((used)) static void conf_message_callback(const char *s)
{
	if (save_and_exit) {
		if (!silent)
			printf("%s", s);
	} else {
		show_textbox(NULL, s, 6, 60);
	}
}