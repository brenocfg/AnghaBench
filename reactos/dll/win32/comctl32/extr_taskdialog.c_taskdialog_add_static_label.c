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
struct taskdialog_template_desc {int /*<<< orphan*/  dialog_height; TYPE_1__* taskconfig; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {scalar_t__ cy; int /*<<< orphan*/  cx; } ;
struct TYPE_4__ {int /*<<< orphan*/  hInstance; } ;
typedef  TYPE_2__ SIZE ;

/* Variables and functions */
 scalar_t__ DIALOG_SPACING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WC_STATICW ; 
 unsigned int taskdialog_add_control (struct taskdialog_template_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  taskdialog_get_text_extent (struct taskdialog_template_desc*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static unsigned int taskdialog_add_static_label(struct taskdialog_template_desc *desc, WORD id, const WCHAR *str)
{
    unsigned int size;
    SIZE sz;

    if (!str)
        return 0;

    taskdialog_get_text_extent(desc, str, TRUE, &sz);

    desc->dialog_height += DIALOG_SPACING;
    size = taskdialog_add_control(desc, id, WC_STATICW, desc->taskconfig->hInstance, str, 0, DIALOG_SPACING,
            desc->dialog_height, sz.cx, sz.cy);
    desc->dialog_height += sz.cy + DIALOG_SPACING;
    return size;
}