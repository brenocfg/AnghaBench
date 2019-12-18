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
 void* RegisterWindowMessageW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZOLEUI_MSG_ENDDIALOGW ; 
 int /*<<< orphan*/  SZOLEUI_MSG_HELPW ; 
 void* oleui_msg_enddialog ; 
 void* oleui_msg_help ; 

__attribute__((used)) static void register_messages(void)
{
    oleui_msg_help             = RegisterWindowMessageW(SZOLEUI_MSG_HELPW);
    oleui_msg_enddialog        = RegisterWindowMessageW(SZOLEUI_MSG_ENDDIALOGW);
}