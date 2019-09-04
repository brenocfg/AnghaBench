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
struct TYPE_4__ {int direction; struct snd_compr_runtime* runtime; struct snd_compr* device; int /*<<< orphan*/  private_data; TYPE_1__* ops; int /*<<< orphan*/  error_work; } ;
struct snd_compr_runtime {TYPE_2__ stream; int /*<<< orphan*/  sleep; int /*<<< orphan*/  state; } ;
struct snd_compr_file {TYPE_2__ stream; int /*<<< orphan*/  sleep; int /*<<< orphan*/  state; } ;
struct snd_compr {int direction; int /*<<< orphan*/  card; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  private_data; } ;
struct inode {int dummy; } ;
struct file {int f_flags; void* private_data; } ;
typedef  enum snd_compr_direction { ____Placeholder_snd_compr_direction } snd_compr_direction ;
struct TYPE_3__ {int (* open ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int EBADFD ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_COMPRESS ; 
 int /*<<< orphan*/  SNDRV_PCM_STATE_OPEN ; 
 int SND_COMPRESS_CAPTURE ; 
 int SND_COMPRESS_PLAYBACK ; 
 int /*<<< orphan*/  error_delayed_work ; 
 int imajor (struct inode*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_compr_runtime*) ; 
 struct snd_compr_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  snd_card_unref (int /*<<< orphan*/ ) ; 
 struct snd_compr* snd_lookup_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_major ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int snd_compr_open(struct inode *inode, struct file *f)
{
	struct snd_compr *compr;
	struct snd_compr_file *data;
	struct snd_compr_runtime *runtime;
	enum snd_compr_direction dirn;
	int maj = imajor(inode);
	int ret;

	if ((f->f_flags & O_ACCMODE) == O_WRONLY)
		dirn = SND_COMPRESS_PLAYBACK;
	else if ((f->f_flags & O_ACCMODE) == O_RDONLY)
		dirn = SND_COMPRESS_CAPTURE;
	else
		return -EINVAL;

	if (maj == snd_major)
		compr = snd_lookup_minor_data(iminor(inode),
					SNDRV_DEVICE_TYPE_COMPRESS);
	else
		return -EBADFD;

	if (compr == NULL) {
		pr_err("no device data!!!\n");
		return -ENODEV;
	}

	if (dirn != compr->direction) {
		pr_err("this device doesn't support this direction\n");
		snd_card_unref(compr->card);
		return -EINVAL;
	}

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		snd_card_unref(compr->card);
		return -ENOMEM;
	}

	INIT_DELAYED_WORK(&data->stream.error_work, error_delayed_work);

	data->stream.ops = compr->ops;
	data->stream.direction = dirn;
	data->stream.private_data = compr->private_data;
	data->stream.device = compr;
	runtime = kzalloc(sizeof(*runtime), GFP_KERNEL);
	if (!runtime) {
		kfree(data);
		snd_card_unref(compr->card);
		return -ENOMEM;
	}
	runtime->state = SNDRV_PCM_STATE_OPEN;
	init_waitqueue_head(&runtime->sleep);
	data->stream.runtime = runtime;
	f->private_data = (void *)data;
	mutex_lock(&compr->lock);
	ret = compr->ops->open(&data->stream);
	mutex_unlock(&compr->lock);
	if (ret) {
		kfree(runtime);
		kfree(data);
	}
	snd_card_unref(compr->card);
	return ret;
}