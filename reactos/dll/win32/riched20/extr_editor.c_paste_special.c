#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ cfFormat; } ;
struct paste_format {scalar_t__ (* paste ) (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ;TYPE_4__ fmt; } ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int styleFlags; } ;
struct TYPE_9__ {scalar_t__ dwAspect; } ;
typedef  int /*<<< orphan*/  STGMEDIUM ;
typedef  TYPE_1__ REPASTESPECIAL ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  scalar_t__ HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CF_TEXT ; 
 scalar_t__ CF_UNICODETEXT ; 
 scalar_t__ DVASPECT_CONTENT ; 
 int ES_READONLY ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ IDataObject_GetData (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IDataObject_QueryGetData (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MB_ICONERROR ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 scalar_t__ OleGetClipboard (int /*<<< orphan*/ **) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  init_paste_formats () ; 
 struct paste_format* paste_formats ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL paste_special(ME_TextEditor *editor, UINT cf, REPASTESPECIAL *ps, BOOL check_only)
{
    HRESULT hr;
    STGMEDIUM med;
    struct paste_format *format;
    IDataObject *data;

    /* Protect read-only edit control from modification */
    if (editor->styleFlags & ES_READONLY)
    {
        if (!check_only)
            MessageBeep(MB_ICONERROR);
        return FALSE;
    }

    init_paste_formats();

    if (ps && ps->dwAspect != DVASPECT_CONTENT)
        FIXME("Ignoring aspect %x\n", ps->dwAspect);

    hr = OleGetClipboard( &data );
    if (hr != S_OK) return FALSE;

    if (cf == CF_TEXT) cf = CF_UNICODETEXT;

    hr = S_FALSE;
    for (format = paste_formats; format->fmt.cfFormat; format++)
    {
        if (cf && cf != format->fmt.cfFormat) continue;
        hr = IDataObject_QueryGetData( data, &format->fmt );
        if (hr == S_OK)
        {
            if (!check_only)
            {
                hr = IDataObject_GetData( data, &format->fmt, &med );
                if (hr != S_OK) goto done;
                hr = format->paste( editor, &format->fmt, &med );
            }
            break;
        }
    }

done:
    IDataObject_Release( data );

    return hr == S_OK;
}