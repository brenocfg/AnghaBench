#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  virtio_block_fd; int /*<<< orphan*/  block_dp; } ;
struct mic_info {TYPE_2__ mic_virtblk; int /*<<< orphan*/  name; } ;
struct _mic_vring_info {int dummy; } ;
struct TYPE_4__ {int num_vq; } ;
struct TYPE_6__ {TYPE_1__ dd; } ;

/* Variables and functions */
 scalar_t__ MIC_DEVICE_PAGE_END ; 
 int /*<<< orphan*/  MIC_VIRTIO_RING_ALIGN ; 
 int /*<<< orphan*/  MIC_VRING_ENTRIES ; 
 int PAGE_ALIGN (scalar_t__) ; 
 scalar_t__ _vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__ virtblk_dev_page ; 

__attribute__((used)) static void
stop_virtblk(struct mic_info *mic)
{
	int vr_size, ret;

	vr_size = PAGE_ALIGN(_vring_size(MIC_VRING_ENTRIES,
					 MIC_VIRTIO_RING_ALIGN) +
			     sizeof(struct _mic_vring_info));
	ret = munmap(mic->mic_virtblk.block_dp,
		MIC_DEVICE_PAGE_END + vr_size * virtblk_dev_page.dd.num_vq);
	if (ret < 0)
		mpsslog("%s munmap errno %d\n", mic->name, errno);
	close(mic->mic_virtblk.virtio_block_fd);
}