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
typedef  void* XtPointer ;
struct TYPE_5__ {char* addr; int size; } ;
typedef  TYPE_1__ XrmValue ;
struct TYPE_6__ {int /*<<< orphan*/  menu_font; scalar_t__ rsrc_menu_font_name; int /*<<< orphan*/  menu_fontset; } ;
typedef  int /*<<< orphan*/  GuiFontset ;
typedef  int /*<<< orphan*/  GuiFont ;

/* Variables and functions */
 scalar_t__ False ; 
 scalar_t__ XtConvertAndStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XtRFontSet ; 
 int /*<<< orphan*/  XtRFontStruct ; 
 int /*<<< orphan*/  XtRString ; 
 TYPE_2__ gui ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  vimShell ; 

void
gui_init_menu_font()
{
    XrmValue from, to;

#ifdef FONTSET_ALWAYS
    from.addr = (char *)gui.rsrc_menu_font_name;
    from.size = strlen(from.addr);
    to.addr = (XtPointer)&gui.menu_fontset;
    to.size = sizeof(GuiFontset);

    if (XtConvertAndStore(vimShell, XtRString, &from, XtRFontSet, &to) == False)
    {
	/* Failed. What to do? */
    }
#else
    from.addr = (char *)gui.rsrc_menu_font_name;
    from.size = strlen(from.addr);
    to.addr = (XtPointer)&gui.menu_font;
    to.size = sizeof(GuiFont);

    if (XtConvertAndStore(vimShell, XtRString, &from, XtRFontStruct, &to) == False)
    {
	/* Failed. What to do? */
    }
#endif
}