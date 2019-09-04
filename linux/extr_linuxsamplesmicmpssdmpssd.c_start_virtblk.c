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
struct mic_vring {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  virtio_block_fd; } ;
struct mic_info {int /*<<< orphan*/  name; TYPE_1__ mic_virtblk; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_vq; } ;
struct TYPE_5__ {TYPE_3__ dd; int /*<<< orphan*/  blk_config; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  VIRTIO_ID_BLOCK ; 
 int /*<<< orphan*/  add_virtio_device (struct mic_info*,TYPE_3__*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ init_vr (struct mic_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mic_vring*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpsslog (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 TYPE_2__ virtblk_dev_page ; 

__attribute__((used)) static bool
start_virtblk(struct mic_info *mic, struct mic_vring *vring)
{
	if (((unsigned long)&virtblk_dev_page.blk_config % 8) != 0) {
		mpsslog("%s: blk_config is not 8 byte aligned.\n",
			mic->name);
		return false;
	}
	add_virtio_device(mic, &virtblk_dev_page.dd);
	if (MAP_FAILED == init_vr(mic, mic->mic_virtblk.virtio_block_fd,
				  VIRTIO_ID_BLOCK, vring, NULL,
				  virtblk_dev_page.dd.num_vq)) {
		mpsslog("%s init_vr failed %s\n",
			mic->name, strerror(errno));
		return false;
	}
	return true;
}