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
 int /*<<< orphan*/  btn_dialog (int /*<<< orphan*/ ,char const*,int,char*) ; 
 int /*<<< orphan*/  main_window ; 

__attribute__((used)) static void conf_message_callback(const char *s)
{
	btn_dialog(main_window, s, 1, "<OK>");
}