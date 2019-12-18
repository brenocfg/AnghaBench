#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_unit {int dummy; } ;
struct TYPE_3__ {int syt_override; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct amdtp_stream {int direction; int flags; int callbacked; unsigned int fmt; TYPE_2__ ctx_data; int /*<<< orphan*/ * process_ctx_payloads; int /*<<< orphan*/  callback_wait; scalar_t__ packet_index; int /*<<< orphan*/  period_tasklet; int /*<<< orphan*/  mutex; int /*<<< orphan*/  context; struct fw_unit* unit; int /*<<< orphan*/  protocol; } ;
typedef  enum cip_flags { ____Placeholder_cip_flags } cip_flags ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;
typedef  int /*<<< orphan*/ * amdtp_stream_process_ctx_payloads_t ;

/* Variables and functions */
 int AMDTP_OUT_STREAM ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm_period_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int amdtp_stream_init(struct amdtp_stream *s, struct fw_unit *unit,
		      enum amdtp_stream_direction dir, enum cip_flags flags,
		      unsigned int fmt,
		      amdtp_stream_process_ctx_payloads_t process_ctx_payloads,
		      unsigned int protocol_size)
{
	if (process_ctx_payloads == NULL)
		return -EINVAL;

	s->protocol = kzalloc(protocol_size, GFP_KERNEL);
	if (!s->protocol)
		return -ENOMEM;

	s->unit = unit;
	s->direction = dir;
	s->flags = flags;
	s->context = ERR_PTR(-1);
	mutex_init(&s->mutex);
	tasklet_init(&s->period_tasklet, pcm_period_tasklet, (unsigned long)s);
	s->packet_index = 0;

	init_waitqueue_head(&s->callback_wait);
	s->callbacked = false;

	s->fmt = fmt;
	s->process_ctx_payloads = process_ctx_payloads;

	if (dir == AMDTP_OUT_STREAM)
		s->ctx_data.rx.syt_override = -1;

	return 0;
}