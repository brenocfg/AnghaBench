#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
typedef  int /*<<< orphan*/  XtPointer ;
typedef  int /*<<< orphan*/  XtInputMask ;
typedef  int /*<<< orphan*/  XtCallbackProc ;
typedef  int XmString ;
typedef  int Widget ;
struct TYPE_6__ {int num; int dialog; int ok; int cancel; int name; int encoding_pulldown; int encoding_menu; int* list; int in_pixels; int /*<<< orphan*/ * font_name; int /*<<< orphan*/  old_list; scalar_t__ old; int /*<<< orphan*/  exit; int /*<<< orphan*/ ** sel; void* sample; void* names; } ;
typedef  TYPE_1__ SharedFontSelData ;
typedef  int /*<<< orphan*/  Arg ;

/* Variables and functions */
 size_t ENCODING ; 
 int /*<<< orphan*/  False ; 
 int MAX_DISPLAY_SIZE ; 
 int MAX_FONTS ; 
 int MAX_FONT_NAME_LEN ; 
 size_t NAME ; 
 int /*<<< orphan*/  NONE ; 
 char NUL ; 
 size_t SIZE ; 
 size_t STYLE ; 
 int TEMP_BUF_SIZE ; 
 int True ; 
 int /*<<< orphan*/  XFreeFont (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XFreeFontNames (char**) ; 
 void* XListFonts (int /*<<< orphan*/ ,char*,int,int*) ; 
 scalar_t__ XLoadQueryFont (int /*<<< orphan*/ ,char*) ; 
 int XmALIGNMENT_BEGINNING ; 
 int XmALIGNMENT_CENTER ; 
 int XmATTACH_FORM ; 
 int /*<<< orphan*/  XmATTACH_OPPOSITE_WIDGET ; 
 int /*<<< orphan*/  XmATTACH_POSITION ; 
 int XmATTACH_WIDGET ; 
 int /*<<< orphan*/  XmAddTabGroup (int) ; 
 int XmCONSTANT ; 
 int XmCreateDialogShell (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int XmCreateOptionMenu (int,char*,int /*<<< orphan*/ *,int) ; 
 int XmCreatePulldownMenu (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* XmCreateScrolledList (int,char*,int /*<<< orphan*/ *,int) ; 
 int XmCreateSeparatorGadget (int,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XmDIALOG_FULL_APPLICATION_MODAL ; 
 int XmFRAME_TITLE_CHILD ; 
 int /*<<< orphan*/  XmFontListFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmNactivateCallback ; 
 int /*<<< orphan*/  XmNalignment ; 
 int /*<<< orphan*/  XmNautoUnmanage ; 
 int /*<<< orphan*/  XmNbottomAttachment ; 
 int /*<<< orphan*/  XmNbottomOffset ; 
 int /*<<< orphan*/  XmNbottomWidget ; 
 int /*<<< orphan*/  XmNbrowseSelectionCallback ; 
 int /*<<< orphan*/  XmNcancelButton ; 
 int /*<<< orphan*/  XmNchildHorizontalAlignment ; 
 int /*<<< orphan*/  XmNchildType ; 
 int /*<<< orphan*/  XmNchildVerticalAlignment ; 
 int /*<<< orphan*/  XmNcolumns ; 
 int /*<<< orphan*/  XmNdialogStyle ; 
 int /*<<< orphan*/  XmNdialogTitle ; 
 int /*<<< orphan*/  XmNeditMode ; 
 int /*<<< orphan*/  XmNeditable ; 
 int /*<<< orphan*/  XmNfontList ; 
 int /*<<< orphan*/  XmNlabelString ; 
 int /*<<< orphan*/  XmNleftAttachment ; 
 int /*<<< orphan*/  XmNleftOffset ; 
 int /*<<< orphan*/  XmNleftPosition ; 
 int /*<<< orphan*/  XmNleftWidget ; 
 int /*<<< orphan*/  XmNlistSizePolicy ; 
 int /*<<< orphan*/  XmNmaxLength ; 
 int /*<<< orphan*/  XmNorientation ; 
 int /*<<< orphan*/  XmNrecomputeSize ; 
 int /*<<< orphan*/  XmNresizable ; 
 int /*<<< orphan*/  XmNrightAttachment ; 
 int /*<<< orphan*/  XmNrightOffset ; 
 int /*<<< orphan*/  XmNrightPosition ; 
 int /*<<< orphan*/  XmNrightWidget ; 
 int /*<<< orphan*/  XmNshadowThickness ; 
 int /*<<< orphan*/  XmNshadowType ; 
 int /*<<< orphan*/  XmNshowAsDefault ; 
 int /*<<< orphan*/  XmNsubMenuId ; 
 int /*<<< orphan*/  XmNtopAttachment ; 
 int /*<<< orphan*/  XmNtopOffset ; 
 int /*<<< orphan*/  XmNtopWidget ; 
 int /*<<< orphan*/  XmNuserData ; 
 int /*<<< orphan*/  XmNvalueChangedCallback ; 
 int /*<<< orphan*/  XmNvisibleItemCount ; 
 int /*<<< orphan*/  XmNvisualPolicy ; 
 int /*<<< orphan*/  XmProcessTraversal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XmSHADOW_ETCHED_IN ; 
 int /*<<< orphan*/  XmSINGLE_LINE_EDIT ; 
 int XmStringCreateLocalized (char*) ; 
 int /*<<< orphan*/  XmStringFree (int) ; 
 int /*<<< orphan*/  XmTRAVERSE_CURRENT ; 
 int /*<<< orphan*/  XmTextSetString (int,int /*<<< orphan*/ *) ; 
 int XmVARIABLE ; 
 int XmVERTICAL ; 
 int /*<<< orphan*/  XtAddCallback (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtAppProcessEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtDestroyWidget (int) ; 
 int /*<<< orphan*/  XtDisplay (int) ; 
 scalar_t__ XtIMAll ; 
 int /*<<< orphan*/  XtManageChild (int) ; 
 void* XtNewString (char*) ; 
 int /*<<< orphan*/  XtSetArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* XtVaCreateManagedWidget (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,...) ; 
 int XtVaCreateWidget (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtVaSetValues (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtWidgetToApplicationContext (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_cancel_action (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  apply_fontlist (int) ; 
 int atoi (char*) ; 
 scalar_t__ cancel_callback ; 
 int /*<<< orphan*/  display_sample (TYPE_1__*) ; 
 int /*<<< orphan*/  encoding_part (char*,char*) ; 
 int /*<<< orphan*/  fill_lists (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_part (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  gui_motif_create_fontlist (scalar_t__) ; 
 int /*<<< orphan*/  gui_motif_synch_fonts () ; 
 int /*<<< orphan*/  manage_centered (int) ; 
 scalar_t__ name_callback ; 
 int /*<<< orphan*/  name_part (char*,char*) ; 
 scalar_t__ ok_callback ; 
 scalar_t__ size_callback ; 
 int /*<<< orphan*/  size_part (char*,char*,int) ; 
 scalar_t__ stoggle_callback ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ style_callback ; 
 int /*<<< orphan*/  style_part (char*,char*) ; 
 int vimShell ; 
 int /*<<< orphan*/  xmFormWidgetClass ; 
 int /*<<< orphan*/  xmFrameWidgetClass ; 
 int /*<<< orphan*/  xmLabelGadgetClass ; 
 int /*<<< orphan*/  xmLabelWidgetClass ; 
 int /*<<< orphan*/  xmPushButtonGadgetClass ; 
 int /*<<< orphan*/  xmTextWidgetClass ; 
 int /*<<< orphan*/  xmToggleButtonGadgetClass ; 

char_u *
gui_xm_select_font(char_u *current)
{
    static SharedFontSelData	_data;

    Widget		parent;
    Widget		form;
    Widget		separator;
    Widget		sub_form;
    Widget		size_toggle;
    Widget		name;
    Widget		disp_frame;
    Widget		frame;
    Arg			args[64];
    int			n;
    XmString		str;
    char		big_font[MAX_FONT_NAME_LEN];
    SharedFontSelData	*data;

    data = &_data;

    parent = vimShell;
    data->names = XListFonts(XtDisplay(parent), "-*-*-*-*-*-*-*-*-*-*-*-*-*-*",
						       MAX_FONTS, &data->num);

    /*
     * Find the name of the biggest font less than the given limit
     * MAX_DISPLAY_SIZE used to set up the initial height of the display
     * widget.
     */

    {
	int	i;
	int	max;
	int	idx = 0;
	int	size;
	char	buf[128];

	for (i = 0, max = 0; i < data->num; i++)
	{
	    get_part(fn(data, i), 7, buf);
	    size = atoi(buf);
	    if ((size > max) && (size < MAX_DISPLAY_SIZE))
	    {
		idx = i;
		max = size;
	    }
	}
	strcpy(big_font, fn(data, idx));
    }
    data->old = XLoadQueryFont(XtDisplay(parent), big_font);
    data->old_list = gui_motif_create_fontlist(data->old);

    /* Set the title of the Dialog window. */
    data->dialog = XmCreateDialogShell(parent, "fontSelector", NULL, 0);
    str = XmStringCreateLocalized(_("Vim - Font Selector"));

    /* Create form popup dialog widget. */
    form = XtVaCreateWidget("form",
	    xmFormWidgetClass, data->dialog,
	    XmNdialogTitle, str,
	    XmNautoUnmanage, False,
	    XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
	    NULL);
    XmStringFree(str);

    sub_form = XtVaCreateManagedWidget("subForm",
	    xmFormWidgetClass, form,
	    XmNbottomAttachment, XmATTACH_FORM,
	    XmNbottomOffset, 4,
	    XmNrightAttachment, XmATTACH_FORM,
	    XmNrightOffset, 4,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNtopOffset, 4,
	    XmNorientation, XmVERTICAL,
	    NULL);

    data->ok = XtVaCreateManagedWidget(_("OK"),
	    xmPushButtonGadgetClass, sub_form,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNrightAttachment, XmATTACH_FORM,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNtopOffset, 4,
	    NULL);
    apply_fontlist(data->ok);

    data->cancel = XtVaCreateManagedWidget(_("Cancel"),
	    xmPushButtonGadgetClass, sub_form,
	    XmNrightAttachment, XmATTACH_FORM,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNtopAttachment, XmATTACH_WIDGET,
	    XmNtopWidget, data->ok,
	    XmNtopOffset, 4,
	    XmNshowAsDefault, True,
	    NULL);
    apply_fontlist(data->cancel);

    /* Create the separator for beauty. */
    n = 0;
    XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET); n++;
    XtSetArg(args[n], XmNrightWidget, sub_form); n++;
    XtSetArg(args[n], XmNrightOffset, 4); n++;
    separator = XmCreateSeparatorGadget(form, "separator", args, n);
    XtManageChild(separator);

    /* Create font name text widget and the corresponding label. */
    data->name = XtVaCreateManagedWidget("fontName",
	    xmTextWidgetClass, form,
	    XmNbottomAttachment, XmATTACH_FORM,
	    XmNbottomOffset, 4,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNleftOffset, 4,
	    XmNrightAttachment, XmATTACH_WIDGET,
	    XmNrightWidget, separator,
	    XmNrightOffset, 4,
	    XmNeditable, False,
	    XmNeditMode, XmSINGLE_LINE_EDIT,
	    XmNmaxLength, MAX_FONT_NAME_LEN,
	    XmNcolumns, 60,
	    NULL);

    str = XmStringCreateLocalized(_("Name:"));
    name = XtVaCreateManagedWidget("fontNameLabel",
	    xmLabelGadgetClass, form,
	    XmNlabelString, str,
	    XmNuserData, data->name,
	    XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
	    XmNleftWidget, data->name,
	    XmNbottomAttachment, XmATTACH_WIDGET,
	    XmNbottomWidget, data->name,
	    XmNtopOffset, 1,
	    NULL);
    XmStringFree(str);
    apply_fontlist(name);

    /* create sample display label widget */
    disp_frame = XtVaCreateManagedWidget("sampleFrame",
	    xmFrameWidgetClass, form,
	    XmNshadowType, XmSHADOW_ETCHED_IN,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNleftOffset, 4,
	    XmNbottomAttachment, XmATTACH_WIDGET,
	    XmNbottomWidget, name,
	    XmNrightAttachment, XmATTACH_WIDGET,
	    XmNrightWidget, separator,
	    XmNrightOffset, 4,
	    XmNalignment, XmALIGNMENT_BEGINNING,
	    NULL);

    data->sample = XtVaCreateManagedWidget("sampleLabel",
	    xmLabelWidgetClass, disp_frame,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNbottomAttachment, XmATTACH_FORM,
	    XmNrightAttachment, XmATTACH_FORM,
	    XmNalignment, XmALIGNMENT_BEGINNING,
	    XmNrecomputeSize, False,
	    XmNfontList, data->old_list,
	    NULL);

    /* create toggle button */
    str = XmStringCreateLocalized(_("Show size in Points"));
    size_toggle = XtVaCreateManagedWidget("sizeToggle",
	    xmToggleButtonGadgetClass, form,
	    XmNlabelString, str,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNleftOffset, 4,
	    XmNbottomAttachment, XmATTACH_WIDGET,
	    XmNbottomWidget, disp_frame,
	    XmNbottomOffset, 4,
	    NULL);
    XmStringFree(str);
    apply_fontlist(size_toggle);
    XtManageChild(size_toggle);

    /* Encoding pulldown menu.
     */

    data->encoding_pulldown = XmCreatePulldownMenu(form,
						 "encodingPulldown", NULL, 0);
    str = XmStringCreateLocalized(_("Encoding:"));
    n = 0;
    XtSetArg(args[n], XmNsubMenuId, data->encoding_pulldown); ++n;
    XtSetArg(args[n], XmNlabelString, str); ++n;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); ++n;
    XtSetArg(args[n], XmNleftOffset, 4); ++n;
    XtSetArg(args[n], XmNbottomAttachment, XmATTACH_WIDGET); ++n;
    XtSetArg(args[n], XmNbottomWidget, size_toggle); ++n;
    XtSetArg(args[n], XmNbottomOffset, 4); ++n;
    XtSetArg(args[n], XmNrightAttachment, XmATTACH_WIDGET); ++n;
    XtSetArg(args[n], XmNrightWidget, separator); ++n;
    XtSetArg(args[n], XmNrightOffset, 4); ++n;
    data->encoding_menu = XmCreateOptionMenu(form, "encodingMenu", args, n);
    XmStringFree(str);
    XmAddTabGroup(data->encoding_menu);

    /*
     * Create scroll list widgets in a separate subform used to manage the
     * different sizes of the lists.
     */

    sub_form = XtVaCreateManagedWidget("subForm",
	    xmFormWidgetClass, form,
	    XmNbottomAttachment, XmATTACH_WIDGET,
	    XmNbottomWidget, data->encoding_menu,
	    XmNbottomOffset, 4,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNleftOffset, 4,
	    XmNrightAttachment, XmATTACH_WIDGET,
	    XmNrightWidget, separator,
	    XmNrightOffset, 4,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNtopOffset, 2,
	    XmNorientation, XmVERTICAL,
	    NULL);

    /* font list */
    frame = XtVaCreateManagedWidget("frame", xmFrameWidgetClass, sub_form,
	    XmNshadowThickness, 0,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNbottomAttachment, XmATTACH_FORM,
	    XmNleftAttachment, XmATTACH_FORM,
	    XmNrightAttachment, XmATTACH_POSITION,
	    XmNrightPosition, 50,
	    NULL);

    str = XmStringCreateLocalized(_("Font:"));
    name = XtVaCreateManagedWidget("nameListLabel", xmLabelGadgetClass, frame,
	    XmNchildType, XmFRAME_TITLE_CHILD,
	    XmNchildVerticalAlignment, XmALIGNMENT_CENTER,
	    XmNchildHorizontalAlignment, XmALIGNMENT_BEGINNING,
	    XmNlabelString, str,
	    NULL);
    XmStringFree(str);
    apply_fontlist(name);

    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 8); ++n;
    XtSetArg(args[n], XmNresizable, True); ++n;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT); ++n;
    XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE); ++n;
#ifdef LESSTIF_VERSION
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC); ++n;
#endif
    data->list[NAME] = XmCreateScrolledList(frame, "fontList", args, n);
    XtVaSetValues(name, XmNuserData, data->list[NAME], NULL);

    /* style list */
    frame = XtVaCreateManagedWidget("frame", xmFrameWidgetClass, sub_form,
	    XmNshadowThickness, 0,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNbottomAttachment, XmATTACH_FORM,
	    XmNleftAttachment, XmATTACH_POSITION,
	    XmNleftPosition, 50,
	    XmNleftOffset, 4,
	    XmNrightAttachment, XmATTACH_POSITION,
	    XmNrightPosition, 80,
	    NULL);

    str = XmStringCreateLocalized(_("Style:"));
    name = XtVaCreateManagedWidget("styleListLabel", xmLabelWidgetClass, frame,
	    XmNchildType, XmFRAME_TITLE_CHILD,
	    XmNchildVerticalAlignment, XmALIGNMENT_CENTER,
	    XmNchildHorizontalAlignment, XmALIGNMENT_BEGINNING,
	    XmNlabelString, str,
	    NULL);
    XmStringFree(str);
    apply_fontlist(name);

    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 8); ++n;
    XtSetArg(args[n], XmNresizable, True); ++n;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT); ++n;
    XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE); ++n;
#ifdef LESSTIF_VERSION
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC); ++n;
#endif
    data->list[STYLE] = XmCreateScrolledList(frame, "styleList", args, n);
    XtVaSetValues(name, XmNuserData, data->list[STYLE], NULL);

    /* size list */
    frame = XtVaCreateManagedWidget("frame", xmFrameWidgetClass, sub_form,
	    XmNshadowThickness, 0,
	    XmNtopAttachment, XmATTACH_FORM,
	    XmNbottomAttachment, XmATTACH_FORM,
	    XmNleftAttachment, XmATTACH_POSITION,
	    XmNleftPosition, 80,
	    XmNleftOffset, 4,
	    XmNrightAttachment, XmATTACH_FORM,
	    NULL);

    str = XmStringCreateLocalized(_("Size:"));
    name = XtVaCreateManagedWidget("sizeListLabel", xmLabelGadgetClass, frame,
	    XmNchildType, XmFRAME_TITLE_CHILD,
	    XmNchildVerticalAlignment, XmALIGNMENT_CENTER,
	    XmNchildHorizontalAlignment, XmALIGNMENT_BEGINNING,
	    XmNlabelString, str,
	    NULL);
    XmStringFree(str);
    apply_fontlist(name);

    n = 0;
    XtSetArg(args[n], XmNvisibleItemCount, 8); ++n;
    XtSetArg(args[n], XmNresizable, True); ++n;
    XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT); ++n;
    XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE); ++n;
#ifdef LESSTIF_VERSION
    XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC); ++n;
#endif
    data->list[SIZE] = XmCreateScrolledList(frame, "sizeList", args, n);
    XtVaSetValues(name, XmNuserData, data->list[SIZE], NULL);

    /* update form widgets cancel button */
    XtVaSetValues(form, XmNcancelButton, data->cancel, NULL);

    XtAddCallback(size_toggle, XmNvalueChangedCallback,
	    (XtCallbackProc)stoggle_callback, (XtPointer)data);
    XtAddCallback(data->list[NAME], XmNbrowseSelectionCallback,
	    (XtCallbackProc)name_callback, (XtPointer)data);
    XtAddCallback(data->list[STYLE], XmNbrowseSelectionCallback,
	    (XtCallbackProc)style_callback, (XtPointer)data);
    XtAddCallback(data->list[SIZE], XmNbrowseSelectionCallback,
	    (XtCallbackProc)size_callback, (XtPointer)data);
    XtAddCallback(data->ok, XmNactivateCallback,
	    (XtCallbackProc)ok_callback, (XtPointer)data);
    XtAddCallback(data->cancel, XmNactivateCallback,
	    (XtCallbackProc)cancel_callback, (XtPointer)data);

    XmProcessTraversal(data->list[NAME], XmTRAVERSE_CURRENT);

    /* setup tabgroups */

    XmAddTabGroup(data->list[NAME]);
    XmAddTabGroup(data->list[STYLE]);
    XmAddTabGroup(data->list[SIZE]);
    XmAddTabGroup(size_toggle);
    XmAddTabGroup(data->name);
    XmAddTabGroup(data->ok);
    XmAddTabGroup(data->cancel);

    add_cancel_action(data->dialog, (XtCallbackProc)cancel_callback, data);

    /* Preset selection data. */

    data->exit = False;
    data->in_pixels= True;
    data->sel[ENCODING] = NULL;
    data->sel[NAME] = NULL;
    data->sel[STYLE] = NULL;
    data->sel[SIZE] = NULL;
    data->font_name = NULL;

    /* set up current font parameters */
    if (current && current[0] != '\0')
    {
	int	    i;
	char	    **names;

	names = XListFonts(XtDisplay(form), (char *) current, 1, &i);

	if (i != 0)
	{
	    char namebuf[TEMP_BUF_SIZE];
	    char stylebuf[TEMP_BUF_SIZE];
	    char sizebuf[TEMP_BUF_SIZE];
	    char encodingbuf[TEMP_BUF_SIZE];
	    char *found;

	    found = names[0];

	    name_part(found, namebuf);
	    style_part(found, stylebuf);
	    size_part(found, sizebuf, data->in_pixels);
	    encoding_part(found, encodingbuf);

	    if (*namebuf != NUL
		    && *stylebuf != NUL
		    && *sizebuf != NUL
		    && *encodingbuf != NUL)
	    {
		data->sel[NAME] = XtNewString(namebuf);
		data->sel[STYLE] = XtNewString(stylebuf);
		data->sel[SIZE] = XtNewString(sizebuf);
		data->sel[ENCODING] = XtNewString(encodingbuf);
		data->font_name = XtNewString(names[0]);
		display_sample(data);
		XmTextSetString(data->name, data->font_name);
	    }
	    else
	    {
		/* We can't preset a symbolic name, which isn't a full font
		 * description. Therefore we just behave the same way as if the
		 * user didn't have selected anything thus far.
		 *
		 * Unfortunately there is no known way to expand an abbreviated
		 * font name.
		 */

		data->font_name = NULL;
	    }
	}
	XFreeFontNames(names);
    }

    fill_lists(NONE, data);

    /* Unfortunately LessTif doesn't align the list widget's properly.  I don't
     * have currently any idea how to fix this problem.
     */
    XtManageChild(data->list[NAME]);
    XtManageChild(data->list[STYLE]);
    XtManageChild(data->list[SIZE]);
    XtManageChild(data->encoding_menu);
    manage_centered(form);

    /* modal event loop */
    while (!data->exit)
	XtAppProcessEvent(XtWidgetToApplicationContext(data->dialog),
							(XtInputMask)XtIMAll);

    if (data->old)
    {
	XFreeFont(XtDisplay(data->dialog),  data->old);
	XmFontListFree(data->old_list);
    }
    XtDestroyWidget(data->dialog);

    gui_motif_synch_fonts();

    return (char_u *) data->font_name;
}