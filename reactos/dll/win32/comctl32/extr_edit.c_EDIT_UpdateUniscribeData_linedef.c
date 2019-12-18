#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/ * font; int /*<<< orphan*/ * text; int /*<<< orphan*/  tabs; int /*<<< orphan*/  tabs_count; } ;
struct TYPE_8__ {double net_length; int index; int /*<<< orphan*/ * ssa; } ;
struct TYPE_7__ {scalar_t__ iTabOrigin; int /*<<< orphan*/  pTabStops; int /*<<< orphan*/  iScale; int /*<<< orphan*/  cTabStops; } ;
typedef  TYPE_1__ SCRIPT_TABDEF ;
typedef  int /*<<< orphan*/ * SCRIPT_STRING_ANALYSIS ;
typedef  TYPE_2__ LINEDEF ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  scalar_t__ HDC ;
typedef  TYPE_3__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdiGetCharDimensions (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 int SSA_FALLBACK ; 
 int SSA_GLYPHS ; 
 int SSA_LINK ; 
 int SSA_TAB ; 
 int /*<<< orphan*/  ScriptStringAnalyse (scalar_t__,int /*<<< orphan*/ *,double,double,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * SelectObject (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SCRIPT_STRING_ANALYSIS EDIT_UpdateUniscribeData_linedef(EDITSTATE *es, HDC dc, LINEDEF *line_def)
{
	if (!line_def)
		return NULL;

	if (line_def->net_length && !line_def->ssa)
	{
		int index = line_def->index;
		HFONT old_font = NULL;
		HDC udc = dc;
		SCRIPT_TABDEF tabdef;
		HRESULT hr;

		if (!udc)
			udc = GetDC(es->hwndSelf);
		if (es->font)
			old_font = SelectObject(udc, es->font);

		tabdef.cTabStops = es->tabs_count;
		tabdef.iScale = GdiGetCharDimensions(udc, NULL, NULL);
		tabdef.pTabStops = es->tabs;
		tabdef.iTabOrigin = 0;

		hr = ScriptStringAnalyse(udc, &es->text[index], line_def->net_length,
                                         (1.5*line_def->net_length+16), -1,
                                         SSA_LINK|SSA_FALLBACK|SSA_GLYPHS|SSA_TAB, -1,
                                         NULL, NULL, NULL, &tabdef, NULL, &line_def->ssa);
		if (FAILED(hr))
		{
			WARN("ScriptStringAnalyse failed (%x)\n",hr);
			line_def->ssa = NULL;
		}

		if (es->font)
			SelectObject(udc, old_font);
		if (udc != dc)
			ReleaseDC(es->hwndSelf, udc);
	}

	return line_def->ssa;
}