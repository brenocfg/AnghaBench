#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msi_dialog ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;scalar_t__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* control_events ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmpW (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UINT dialog_event_handler( msi_dialog *dialog, const WCHAR *event, const WCHAR *argument )
{
    unsigned int i;

    TRACE("handling event %s\n", debugstr_w(event));

    if (!event) return ERROR_SUCCESS;

    for (i = 0; control_events[i].event; i++)
    {
        if (!strcmpW( control_events[i].event, event ))
            return control_events[i].handler( dialog, argument );
    }
    FIXME("unhandled event %s arg(%s)\n", debugstr_w(event), debugstr_w(argument));
    return ERROR_SUCCESS;
}