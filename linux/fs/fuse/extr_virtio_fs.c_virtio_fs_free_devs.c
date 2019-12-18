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
struct virtio_fs_vq {int /*<<< orphan*/ * fud; } ;
struct virtio_fs {unsigned int nvqs; struct virtio_fs_vq* vqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_dev_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_fs_free_devs(struct virtio_fs *fs)
{
	unsigned int i;

	for (i = 0; i < fs->nvqs; i++) {
		struct virtio_fs_vq *fsvq = &fs->vqs[i];

		if (!fsvq->fud)
			continue;

		fuse_dev_free(fsvq->fud);
		fsvq->fud = NULL;
	}
}