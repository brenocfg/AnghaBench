#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct taskdialog_template_desc {struct taskdialog_button_desc* default_button; TYPE_1__* taskconfig; } ;
struct taskdialog_button_desc {int id; int /*<<< orphan*/  hinst; scalar_t__ line; int /*<<< orphan*/  width; int /*<<< orphan*/  const* text; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {scalar_t__ cx; } ;
struct TYPE_4__ {int nDefaultButton; int /*<<< orphan*/  hInstance; } ;
typedef  TYPE_2__ SIZE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COMCTL32_hModule ; 
 int /*<<< orphan*/  DIALOG_BUTTON_WIDTH ; 
 int DIALOG_SPACING ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  taskdialog_get_text_extent (struct taskdialog_template_desc*,int /*<<< orphan*/  const*,scalar_t__,TYPE_2__*) ; 

__attribute__((used)) static void taskdialog_init_button(struct taskdialog_button_desc *button, struct taskdialog_template_desc *desc,
        int id, const WCHAR *text, BOOL custom_button)
{
    SIZE sz;

    taskdialog_get_text_extent(desc, text, custom_button, &sz);

    button->id = id;
    button->text = text;
    button->width = max(DIALOG_BUTTON_WIDTH, sz.cx + DIALOG_SPACING * 2);
    button->line = 0;
    button->hinst = custom_button ? desc->taskconfig->hInstance : COMCTL32_hModule;

    if (id == desc->taskconfig->nDefaultButton)
        desc->default_button = button;
}