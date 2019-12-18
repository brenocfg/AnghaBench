#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  msi_control ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  const* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int MSI_RecordGetInteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int WS_DISABLED ; 
 int WS_EX_CLIENTEDGE ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * dialog_create_window (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_map_events (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int msidbControlAttributesEnabled ; 
 int msidbControlAttributesSunken ; 
 int msidbControlAttributesVisible ; 
 scalar_t__ strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szScrollableText ; 

__attribute__((used)) static msi_control *msi_dialog_add_control( msi_dialog *dialog,
                MSIRECORD *rec, LPCWSTR szCls, DWORD style )
{
    DWORD attributes;
    const WCHAR *text = NULL, *name, *control_type;
    DWORD exstyle = 0;

    name = MSI_RecordGetString( rec, 2 );
    control_type = MSI_RecordGetString( rec, 3 );
    attributes = MSI_RecordGetInteger( rec, 8 );
    if (strcmpW( control_type, szScrollableText )) text = MSI_RecordGetString( rec, 10 );

    TRACE("%s, %s, %08x, %s, %08x\n", debugstr_w(szCls), debugstr_w(name),
          attributes, debugstr_w(text), style);

    if( attributes & msidbControlAttributesVisible )
        style |= WS_VISIBLE;
    if( ~attributes & msidbControlAttributesEnabled )
        style |= WS_DISABLED;
    if( attributes & msidbControlAttributesSunken )
        exstyle |= WS_EX_CLIENTEDGE;

    dialog_map_events( dialog, name );

    return dialog_create_window( dialog, rec, exstyle, szCls, name, text, style, dialog->hwnd );
}