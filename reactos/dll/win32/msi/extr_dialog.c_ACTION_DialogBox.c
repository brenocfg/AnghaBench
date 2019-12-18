#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  const* next_dialog; } ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  event_do_dialog (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/  const*) ; 

INT ACTION_DialogBox( MSIPACKAGE *package, const WCHAR *dialog )
{
    INT r;

    if (package->next_dialog) ERR("Already got next dialog... ignoring it\n");
    package->next_dialog = NULL;

    /* Dialogs are chained through NewDialog, which sets the next_dialog member.
     * We fall out of the loop if we reach a modeless dialog, which immediately
     * returns IDOK, or an EndDialog event, which returns the value corresponding
     * to its argument.
     */
    r = event_do_dialog( package, dialog, NULL, TRUE );
    while (package->next_dialog)
    {
        WCHAR *name = package->next_dialog;

        package->next_dialog = NULL;
        r = event_do_dialog( package, name, NULL, TRUE );
        msi_free( name );
    }
    return r;
}