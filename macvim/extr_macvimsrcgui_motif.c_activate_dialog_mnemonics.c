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
typedef  int /*<<< orphan*/  XtPointer ;
typedef  int /*<<< orphan*/  XtEventHandler ;
typedef  int /*<<< orphan*/  Widget ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  KeyPressMask ; 
 int /*<<< orphan*/  XtAddEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mnemonic_grabs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mnemonic_event ; 

__attribute__((used)) static void
activate_dialog_mnemonics(Widget dialog)
{
    if (!dialog)
	return;

    XtAddEventHandler(dialog, KeyPressMask, False,
			   (XtEventHandler) mnemonic_event, (XtPointer) NULL);
    add_mnemonic_grabs(dialog, dialog);
}