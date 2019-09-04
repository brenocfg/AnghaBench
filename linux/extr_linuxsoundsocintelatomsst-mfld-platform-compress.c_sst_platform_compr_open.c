#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sst_runtime_stream {scalar_t__ id; TYPE_2__* compr_ops; int /*<<< orphan*/  status_lock; } ;
struct snd_compr_stream {struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct sst_runtime_stream* private_data; } ;
struct TYPE_8__ {TYPE_3__* dev; TYPE_2__* compr_ops; } ;
struct TYPE_7__ {TYPE_1__* driver; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* power ) (TYPE_3__*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SST_PLATFORM_INIT ; 
 int /*<<< orphan*/  kfree (struct sst_runtime_stream*) ; 
 struct sst_runtime_stream* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* sst ; 
 int /*<<< orphan*/  sst_set_stream_status (struct sst_runtime_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_platform_compr_open(struct snd_compr_stream *cstream)
{

	int ret_val = 0;
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sst_runtime_stream *stream;

	stream = kzalloc(sizeof(*stream), GFP_KERNEL);
	if (!stream)
		return -ENOMEM;

	spin_lock_init(&stream->status_lock);

	/* get the sst ops */
	if (!sst || !try_module_get(sst->dev->driver->owner)) {
		pr_err("no device available to run\n");
		ret_val = -ENODEV;
		goto out_ops;
	}
	stream->compr_ops = sst->compr_ops;
	stream->id = 0;

	/* Turn on LPE */
	sst->compr_ops->power(sst->dev, true);

	sst_set_stream_status(stream, SST_PLATFORM_INIT);
	runtime->private_data = stream;
	return 0;
out_ops:
	kfree(stream);
	return ret_val;
}