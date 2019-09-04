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
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  free_func_inst; } ;
struct f_ss_opts {struct usb_function_instance func_inst; int /*<<< orphan*/  iso_qlen; int /*<<< orphan*/  bulk_qlen; int /*<<< orphan*/  bulk_buflen; int /*<<< orphan*/  isoc_maxpacket; int /*<<< orphan*/  isoc_interval; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GZERO_BULK_BUFLEN ; 
 int /*<<< orphan*/  GZERO_ISOC_INTERVAL ; 
 int /*<<< orphan*/  GZERO_ISOC_MAXPACKET ; 
 int /*<<< orphan*/  GZERO_SS_BULK_QLEN ; 
 int /*<<< orphan*/  GZERO_SS_ISO_QLEN ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct f_ss_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  source_sink_free_instance ; 
 int /*<<< orphan*/  ss_func_type ; 

__attribute__((used)) static struct usb_function_instance *source_sink_alloc_inst(void)
{
	struct f_ss_opts *ss_opts;

	ss_opts = kzalloc(sizeof(*ss_opts), GFP_KERNEL);
	if (!ss_opts)
		return ERR_PTR(-ENOMEM);
	mutex_init(&ss_opts->lock);
	ss_opts->func_inst.free_func_inst = source_sink_free_instance;
	ss_opts->isoc_interval = GZERO_ISOC_INTERVAL;
	ss_opts->isoc_maxpacket = GZERO_ISOC_MAXPACKET;
	ss_opts->bulk_buflen = GZERO_BULK_BUFLEN;
	ss_opts->bulk_qlen = GZERO_SS_BULK_QLEN;
	ss_opts->iso_qlen = GZERO_SS_ISO_QLEN;

	config_group_init_type_name(&ss_opts->func_inst.group, "",
				    &ss_func_type);

	return &ss_opts->func_inst;
}