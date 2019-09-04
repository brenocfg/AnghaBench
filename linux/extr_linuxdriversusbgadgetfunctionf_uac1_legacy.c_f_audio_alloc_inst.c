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
struct f_uac1_legacy_opts {struct usb_function_instance func_inst; int /*<<< orphan*/  fn_cntl; int /*<<< orphan*/  fn_cap; int /*<<< orphan*/  fn_play; int /*<<< orphan*/  audio_buf_size; int /*<<< orphan*/  req_count; int /*<<< orphan*/  req_buf_size; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_CONTROL ; 
 int /*<<< orphan*/  FILE_PCM_CAPTURE ; 
 int /*<<< orphan*/  FILE_PCM_PLAYBACK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UAC1_AUDIO_BUF_SIZE ; 
 int /*<<< orphan*/  UAC1_OUT_EP_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  UAC1_REQ_COUNT ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_audio_free_inst ; 
 int /*<<< orphan*/  f_uac1_func_type ; 
 struct f_uac1_legacy_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct usb_function_instance *f_audio_alloc_inst(void)
{
	struct f_uac1_legacy_opts *opts;

	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	mutex_init(&opts->lock);
	opts->func_inst.free_func_inst = f_audio_free_inst;

	config_group_init_type_name(&opts->func_inst.group, "",
				    &f_uac1_func_type);

	opts->req_buf_size = UAC1_OUT_EP_MAX_PACKET_SIZE;
	opts->req_count = UAC1_REQ_COUNT;
	opts->audio_buf_size = UAC1_AUDIO_BUF_SIZE;
	opts->fn_play = FILE_PCM_PLAYBACK;
	opts->fn_cap = FILE_PCM_CAPTURE;
	opts->fn_cntl = FILE_CONTROL;
	return &opts->func_inst;
}