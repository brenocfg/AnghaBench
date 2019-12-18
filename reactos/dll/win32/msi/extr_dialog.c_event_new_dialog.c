#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* package; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/  next_dialog; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  msi_dialog_end_dialog (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_event_cleanup_all_subscriptions (TYPE_2__*) ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UINT event_new_dialog( msi_dialog *dialog, const WCHAR *argument )
{
    /* store the name of the next dialog, and signal this one to end */
    dialog->package->next_dialog = strdupW( argument );
    msi_event_cleanup_all_subscriptions( dialog->package );
    msi_dialog_end_dialog( dialog );
    return ERROR_SUCCESS;
}