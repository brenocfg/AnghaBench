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
struct q6asm {int /*<<< orphan*/  adev; int /*<<< orphan*/  slock; struct audio_client** session; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct audio_client {int session; int perf_mode; int stream_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  refcount; int /*<<< orphan*/  adev; int /*<<< orphan*/  io_mode; void* priv; struct q6asm* q6asm; struct device* dev; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  q6asm_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_SYNC_IO_MODE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct audio_client* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct q6asm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct audio_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct audio_client* q6asm_get_audio_client (struct q6asm*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct audio_client *q6asm_audio_client_alloc(struct device *dev, q6asm_cb cb,
					      void *priv, int stream_id,
					      int perf_mode)
{
	struct q6asm *a = dev_get_drvdata(dev->parent);
	struct audio_client *ac;
	unsigned long flags;

	ac = q6asm_get_audio_client(a, stream_id + 1);
	if (ac) {
		dev_err(dev, "Audio Client already active\n");
		return ac;
	}

	ac = kzalloc(sizeof(*ac), GFP_KERNEL);
	if (!ac)
		return ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&a->slock, flags);
	a->session[stream_id + 1] = ac;
	spin_unlock_irqrestore(&a->slock, flags);
	ac->session = stream_id + 1;
	ac->cb = cb;
	ac->dev = dev;
	ac->q6asm = a;
	ac->priv = priv;
	ac->io_mode = ASM_SYNC_IO_MODE;
	ac->perf_mode = perf_mode;
	/* DSP expects stream id from 1 */
	ac->stream_id = 1;
	ac->adev = a->adev;
	kref_init(&ac->refcount);

	init_waitqueue_head(&ac->cmd_wait);
	mutex_init(&ac->cmd_lock);
	spin_lock_init(&ac->lock);

	return ac;
}