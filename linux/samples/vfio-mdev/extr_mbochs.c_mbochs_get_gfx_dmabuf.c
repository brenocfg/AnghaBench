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
typedef  int /*<<< orphan*/  u32 ;
struct mdev_state {int /*<<< orphan*/  ops_lock; } ;
struct mdev_device {int dummy; } ;
struct mbochs_dmabuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int dma_buf_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbochs_dmabuf_export (struct mbochs_dmabuf*) ; 
 struct mbochs_dmabuf* mbochs_dmabuf_find_by_id (struct mdev_state*,int /*<<< orphan*/ ) ; 
 struct mdev_state* mdev_get_drvdata (struct mdev_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mbochs_get_gfx_dmabuf(struct mdev_device *mdev,
				 u32 id)
{
	struct mdev_state *mdev_state = mdev_get_drvdata(mdev);
	struct mbochs_dmabuf *dmabuf;

	mutex_lock(&mdev_state->ops_lock);

	dmabuf = mbochs_dmabuf_find_by_id(mdev_state, id);
	if (!dmabuf) {
		mutex_unlock(&mdev_state->ops_lock);
		return -ENOENT;
	}

	if (!dmabuf->buf)
		mbochs_dmabuf_export(dmabuf);

	mutex_unlock(&mdev_state->ops_lock);

	if (!dmabuf->buf)
		return -EINVAL;

	return dma_buf_fd(dmabuf->buf, 0);
}