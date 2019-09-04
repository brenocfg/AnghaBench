#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guint ;
struct TYPE_3__ {int /*<<< orphan*/ * (* constructor ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  Main ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkVBox ;
typedef  int /*<<< orphan*/  GtkLabel ;
typedef  int /*<<< orphan*/  GtkHBox ;
typedef  int /*<<< orphan*/  GtkContainer ;
typedef  int /*<<< orphan*/  GtkButton ;
typedef  int /*<<< orphan*/  GType ;
typedef  int /*<<< orphan*/  GObjectConstructParam ;
typedef  TYPE_1__ GObjectClass ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_WINDOW_TOPLEVEL ; 
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _g_object_unref0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_object_ref_sink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_hbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_label_new (char*) ; 
 scalar_t__ gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_parent_class ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GObject * main_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	Main * self;
	GtkVBox* _vbox0 = NULL;
	GtkLabel* _label0 = NULL;
	GtkHBox* _hbox0 = NULL;
	GtkButton* _button0 = NULL;
	GtkButton* _button1 = NULL;
	GtkButton* _button2 = NULL;
	GtkVBox* _tmp0_;
	GtkVBox* _tmp1_;
	GtkLabel* _tmp2_;
	GtkLabel* _tmp3_;
	GtkHBox* _tmp4_;
	GtkHBox* _tmp5_;
	GtkButton* _tmp6_;
	GtkButton* _tmp7_;
	GtkButton* _tmp8_;
	GtkButton* _tmp9_;
	GtkButton* _tmp10_;
	GtkButton* _tmp11_;
	GtkVBox* _tmp12_;
	GtkLabel* _tmp13_;
	GtkHBox* _tmp14_;
	GtkButton* _tmp15_;
	GtkHBox* _tmp16_;
	GtkButton* _tmp17_;
	GtkHBox* _tmp18_;
	GtkButton* _tmp19_;
	GtkVBox* _tmp20_;
	GtkHBox* _tmp21_;
	GtkVBox* _tmp22_;
	parent_class = G_OBJECT_CLASS (main_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = MAIN (obj);
	_tmp0_ = (GtkVBox*) gtk_vbox_new (FALSE, 0);
	_tmp1_ = g_object_ref_sink (_tmp0_);
	_g_object_unref0 (_vbox0);
	_vbox0 = _tmp1_;
	_tmp2_ = (GtkLabel*) gtk_label_new ("hello world");
	_tmp3_ = g_object_ref_sink (_tmp2_);
	_g_object_unref0 (_label0);
	_label0 = _tmp3_;
	_tmp4_ = (GtkHBox*) gtk_hbox_new (FALSE, 0);
	_tmp5_ = g_object_ref_sink (_tmp4_);
	_g_object_unref0 (_hbox0);
	_hbox0 = _tmp5_;
	_tmp6_ = (GtkButton*) gtk_button_new_with_label ("Install");
	_tmp7_ = g_object_ref_sink (_tmp6_);
	_g_object_unref0 (_button0);
	_button0 = _tmp7_;
	_tmp8_ = (GtkButton*) gtk_button_new_with_label ("Update");
	_tmp9_ = g_object_ref_sink (_tmp8_);
	_g_object_unref0 (_button1);
	_button1 = _tmp9_;
	_tmp10_ = (GtkButton*) gtk_button_new_with_label ("Deinstall");
	_tmp11_ = g_object_ref_sink (_tmp10_);
	_g_object_unref0 (_button2);
	_button2 = _tmp11_;
	g_object_set ((GtkWindow*) self, "type", GTK_WINDOW_TOPLEVEL, NULL);
	_tmp12_ = _vbox0;
	_tmp13_ = _label0;
	gtk_container_add ((GtkContainer*) _tmp12_, (GtkWidget*) _tmp13_);
	_tmp14_ = _hbox0;
	_tmp15_ = _button0;
	gtk_container_add ((GtkContainer*) _tmp14_, (GtkWidget*) _tmp15_);
	_tmp16_ = _hbox0;
	_tmp17_ = _button1;
	gtk_container_add ((GtkContainer*) _tmp16_, (GtkWidget*) _tmp17_);
	_tmp18_ = _hbox0;
	_tmp19_ = _button2;
	gtk_container_add ((GtkContainer*) _tmp18_, (GtkWidget*) _tmp19_);
	_tmp20_ = _vbox0;
	_tmp21_ = _hbox0;
	gtk_container_add ((GtkContainer*) _tmp20_, (GtkWidget*) _tmp21_);
	_tmp22_ = _vbox0;
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) _tmp22_);
	_g_object_unref0 (_button2);
	_g_object_unref0 (_button1);
	_g_object_unref0 (_button0);
	_g_object_unref0 (_hbox0);
	_g_object_unref0 (_label0);
	_g_object_unref0 (_vbox0);
	return obj;
}