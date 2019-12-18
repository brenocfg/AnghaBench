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
 int FALSE ; 
 int /*<<< orphan*/  HLF_R ; 
 int /*<<< orphan*/  MSG_PUTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_PUTS_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ got_int ; 
 int /*<<< orphan*/  hl_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_clr_eos () ; 
 scalar_t__ msg_didout ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int /*<<< orphan*/  msg_use_printf () ; 
 int p_more ; 

__attribute__((used)) static void
hit_return_msg()
{
    int		save_p_more = p_more;

    p_more = FALSE;	/* don't want see this message when scrolling back */
    if (msg_didout)	/* start on a new line */
	msg_putchar('\n');
    if (got_int)
	MSG_PUTS(_("Interrupt: "));

    MSG_PUTS_ATTR(_("Press ENTER or type command to continue"), hl_attr(HLF_R));
    if (!msg_use_printf())
	msg_clr_eos();
    p_more = save_p_more;
}