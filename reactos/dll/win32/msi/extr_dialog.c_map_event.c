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
struct dialog_control {int /*<<< orphan*/  control; int /*<<< orphan*/  dialog; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/ * MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  event_subscribe (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UINT map_event( MSIRECORD *row, void *param )
{
    struct dialog_control *dc = param;
    const WCHAR *event = MSI_RecordGetString( row, 3 );
    const WCHAR *attribute = MSI_RecordGetString( row, 4 );

    event_subscribe( dc->dialog, event, dc->control, attribute );
    return ERROR_SUCCESS;
}