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
typedef  enum ListSpecifier { ____Placeholder_ListSpecifier } ListSpecifier ;
typedef  int /*<<< orphan*/  XtPointer ;
typedef  int /*<<< orphan*/  XtCallbackProc ;
typedef  int /*<<< orphan*/  XmString ;
typedef  scalar_t__* WidgetList ;
typedef  scalar_t__ Widget ;
struct TYPE_5__ {int num; char** sel; scalar_t__* list; int /*<<< orphan*/  encoding_menu; int /*<<< orphan*/  encoding_pulldown; int /*<<< orphan*/  in_pixels; } ;
typedef  TYPE_1__ SharedFontSelData ;
typedef  scalar_t__ Cardinal ;

/* Variables and functions */
 int ENCODING ; 
 int /*<<< orphan*/  False ; 
 int MAX_ENTRIES_IN_LIST ; 
#define  NAME 130 
 int NONE ; 
#define  SIZE 129 
#define  STYLE 128 
 int TEMP_BUF_SIZE ; 
 int /*<<< orphan*/  XmListAddItems (scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  XmListDeleteAllItems (scalar_t__) ; 
 int /*<<< orphan*/  XmListSelectItem (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmListSetBottomItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNactivateCallback ; 
 int /*<<< orphan*/  XmNchildren ; 
 int /*<<< orphan*/  XmNlabelString ; 
 int /*<<< orphan*/  XmNmenuHistory ; 
 int /*<<< orphan*/  XmNnumChildren ; 
 int /*<<< orphan*/  XmNuserData ; 
 int /*<<< orphan*/  XmStringCreateLocalized (char*) ; 
 int /*<<< orphan*/  XmStringFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtAddCallback (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtDestroyWidget (scalar_t__) ; 
 int /*<<< orphan*/  XtFree (char*) ; 
 int /*<<< orphan*/  XtManageChild (scalar_t__) ; 
 int /*<<< orphan*/  XtUnmanageChild (scalar_t__) ; 
 scalar_t__ XtVaCreateManagedWidget (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtVaGetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__**,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtVaSetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  add_to_list (char**,char*,int*) ; 
 scalar_t__ encoding_callback ; 
 int /*<<< orphan*/  encoding_part (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fn (TYPE_1__*,int) ; 
 scalar_t__ match (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  name_part (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ proportional (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_part (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  style_part (int /*<<< orphan*/ ,char*) ; 
 char* wild ; 
 int /*<<< orphan*/  xmPushButtonGadgetClass ; 

__attribute__((used)) static void
fill_lists(enum ListSpecifier fix, SharedFontSelData *data)
{
    char	*list[NONE][MAX_ENTRIES_IN_LIST];
    int		count[NONE];
    char	buf[TEMP_BUF_SIZE];
    XmString	items[MAX_ENTRIES_IN_LIST];
    int		i;
    int		idx;

    for (idx = (int)ENCODING; idx < (int)NONE; ++idx)
	count[idx] = 0;

    /* First we insert the wild char into every single list. */
    if (fix != ENCODING)
	add_to_list(list[ENCODING], wild, &count[ENCODING]);
    if (fix != NAME)
	add_to_list(list[NAME], wild, &count[NAME]);
    if (fix != STYLE)
	add_to_list(list[STYLE], wild, &count[STYLE]);
    if (fix != SIZE)
	add_to_list(list[SIZE], wild, &count[SIZE]);

    for (i = 0; i < data->num && i < MAX_ENTRIES_IN_LIST; i++)
    {
	if (proportional(fn(data, i)))
	    continue;

	if (fix != ENCODING
		&& match(data, NAME, i)
		&& match(data, STYLE, i)
		&& match(data, SIZE, i))
	{
	    encoding_part(fn(data, i), buf);
	    add_to_list(list[ENCODING], buf, &count[ENCODING]);
	}

	if (fix != NAME
		&& match(data, ENCODING, i)
		&& match(data, STYLE, i)
		&& match(data, SIZE, i))
	{
	    name_part(fn(data, i), buf);
	    add_to_list(list[NAME], buf, &count[NAME]);
	}

	if (fix != STYLE
		&& match(data, ENCODING, i)
		&& match(data, NAME, i)
		&& match(data, SIZE, i))
	{
	    style_part(fn(data, i), buf);
	    add_to_list(list[STYLE], buf, &count[STYLE]);
	}

	if (fix != SIZE
		&& match(data, ENCODING, i)
		&& match(data, NAME, i)
		&& match(data, STYLE, i))
	{
	    size_part(fn(data, i), buf, data->in_pixels);
	    add_to_list(list[SIZE], buf, &count[SIZE]);
	}
    }

    /*
     * And now do the preselection in all lists where there was one:
     */

    if (fix != ENCODING)
    {
	Cardinal n_items;
	WidgetList children;
	Widget selected_button = 0;

	/* Get and update the current button list.  */
	XtVaGetValues(data->encoding_pulldown,
		XmNchildren, &children,
		XmNnumChildren, &n_items,
		NULL);

	for (i = 0; i < count[ENCODING]; ++i)
	{
	    Widget button;

	    items[i] = XmStringCreateLocalized(list[ENCODING][i]);

	    if (i < (int)n_items)
	    {
		/* recycle old button */
		XtVaSetValues(children[i],
			XmNlabelString, items[i],
			XmNuserData, i,
			NULL);
		button = children[i];
	    }
	    else
	    {
		/* create a new button */
		button = XtVaCreateManagedWidget("button",
			xmPushButtonGadgetClass,
			data->encoding_pulldown,
			XmNlabelString, items[i],
			XmNuserData, i,
			NULL);
		XtAddCallback(button, XmNactivateCallback,
			(XtCallbackProc) encoding_callback, (XtPointer) data);
		XtManageChild(button);
	    }

	    if (data->sel[ENCODING])
	    {
		if (!strcmp(data->sel[ENCODING], list[ENCODING][i]))
		    selected_button = button;
	    }
	    XtFree(list[ENCODING][i]);
	}

	/* Destroy all the outstanding menu items.
	 */
	for (i = count[ENCODING]; i < (int)n_items; ++i)
	{
	    XtUnmanageChild(children[i]);
	    XtDestroyWidget(children[i]);
	}

	/* Preserve the current selection visually.
	 */
	if (selected_button)
	{
	    XtVaSetValues(data->encoding_menu,
		    XmNmenuHistory, selected_button,
		    NULL);
	}

	for (i = 0; i < count[ENCODING]; ++i)
	    XmStringFree(items[i]);
    }

    /*
     * Now loop trough the remaining lists and set them up.
     */
    for (idx = (int)NAME; idx < (int)NONE; ++idx)
    {
	Widget w;

	if (fix == (enum ListSpecifier)idx)
	    continue;

	switch ((enum ListSpecifier)idx)
	{
	    case NAME:
		w = data->list[NAME];
		break;
	    case STYLE:
		w = data->list[STYLE];
		break;
	    case SIZE:
		w = data->list[SIZE];
		break;
	    default:
		w = (Widget)0;	/* for lint */
	}

	for (i = 0; i < count[idx]; ++i)
	{
	    items[i] = XmStringCreateLocalized(list[idx][i]);
	    XtFree(list[idx][i]);
	}
	XmListDeleteAllItems(w);
	XmListAddItems(w, items, count[idx], 1);
	if (data->sel[idx])
	{
	    XmStringFree(items[0]);
	    items[0] = XmStringCreateLocalized(data->sel[idx]);
	    XmListSelectItem(w, items[0], False);
	    XmListSetBottomItem(w, items[0]);
	}
	for (i = 0; i < count[idx]; ++i)
	    XmStringFree(items[i]);
    }
}