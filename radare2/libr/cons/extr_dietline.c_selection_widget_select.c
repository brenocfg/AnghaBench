#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; size_t length; size_t index; } ;
struct TYPE_6__ {TYPE_1__ buffer; TYPE_2__* sel_widget; } ;
struct TYPE_5__ {size_t selection; size_t options_len; int /*<<< orphan*/ * options; } ;
typedef  TYPE_2__ RSelWidget ;

/* Variables and functions */
 TYPE_3__ I ; 
 scalar_t__ R_LINE_BUFSIZE ; 
 void* R_MIN (size_t,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  selection_widget_erase () ; 
 char* strchr (char*,char) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void selection_widget_select() {
	RSelWidget *sel_widget = I.sel_widget;
	if (sel_widget && sel_widget->selection < sel_widget->options_len) {
		char *sp = strchr (I.buffer.data, ' ');
		if (sp) {
			int delta = sp - I.buffer.data + 1;
			I.buffer.length = R_MIN (delta + strlen (sel_widget->options[sel_widget->selection]), R_LINE_BUFSIZE - 1);
			memcpy (I.buffer.data + delta, sel_widget->options[sel_widget->selection], strlen (sel_widget->options[sel_widget->selection]));
			I.buffer.index = I.buffer.length;
			return;
		}
		I.buffer.length = R_MIN (strlen (sel_widget->options[sel_widget->selection]), R_LINE_BUFSIZE - 1);
		memcpy (I.buffer.data, sel_widget->options[sel_widget->selection], I.buffer.length);
		I.buffer.data[I.buffer.length] = '\0';
		I.buffer.index = I.buffer.length;
		selection_widget_erase ();
	}
}