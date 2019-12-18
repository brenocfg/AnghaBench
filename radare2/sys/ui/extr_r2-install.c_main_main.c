#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  Main ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  _g_object_unref0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_object_ref_sink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_init (int*,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  gtk_main () ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * main_new () ; 

void main_main (gchar** args, int args_length1) {
	Main* _tmp0_;
	Main* _tmp1_;
	Main* m;
	gtk_init (&args_length1, &args);
	_tmp0_ = main_new ();
	_tmp1_ = g_object_ref_sink (_tmp0_);
	m = _tmp1_;
	gtk_widget_show_all ((GtkWidget*) m);
	gtk_main ();
	_g_object_unref0 (m);
}