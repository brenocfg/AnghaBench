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
struct taskdialog_template_desc {int /*<<< orphan*/  control_count; int /*<<< orphan*/  controls; } ;
struct taskdialog_control {unsigned int template_size; int /*<<< orphan*/  entry; TYPE_1__* template; } ;
typedef  int /*<<< orphan*/  nulW ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT_PTR ;
struct TYPE_2__ {int style; short x; short y; short cx; short cy; int /*<<< orphan*/  id; scalar_t__ dwExtendedStyle; } ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int DWORD ;
typedef  TYPE_1__ DLGITEMTEMPLATE ;

/* Variables and functions */
 unsigned int ALIGNED_LENGTH (unsigned int,int) ; 
 void* Alloc (unsigned int) ; 
 scalar_t__ IS_INTRESOURCE (int /*<<< orphan*/  const*) ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  template_write_data (char**,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static unsigned int taskdialog_add_control(struct taskdialog_template_desc *desc, WORD id, const WCHAR *class,
        HINSTANCE hInstance, const WCHAR *text, DWORD style, short x, short y, short cx, short cy)
{
    struct taskdialog_control *control = Alloc(sizeof(*control));
    unsigned int size, class_size, text_size;
    DLGITEMTEMPLATE *template;
    static const WCHAR nulW;
    const WCHAR *textW;
    char *ptr;

    class_size = (strlenW(class) + 1) * sizeof(WCHAR);

    if (IS_INTRESOURCE(text))
        text_size = LoadStringW(hInstance, (UINT_PTR)text, (WCHAR *)&textW, 0) * sizeof(WCHAR);
    else
    {
        textW = text;
        text_size = strlenW(textW) * sizeof(WCHAR);
    }

    size = sizeof(DLGITEMTEMPLATE);
    size += class_size;
    size += text_size + sizeof(WCHAR);
    size += sizeof(WORD); /* creation data */

    control->template = template = Alloc(size);
    control->template_size = size;

    template->style = WS_VISIBLE | style;
    template->dwExtendedStyle = 0;
    template->x = x;
    template->y = y;
    template->cx = cx;
    template->cy = cy;
    template->id = id;
    ptr = (char *)(template + 1);
    template_write_data(&ptr, class, class_size);
    template_write_data(&ptr, textW, text_size);
    template_write_data(&ptr, &nulW, sizeof(nulW));

    list_add_tail(&desc->controls, &control->entry);
    desc->control_count++;
    return ALIGNED_LENGTH(size, 3);
}