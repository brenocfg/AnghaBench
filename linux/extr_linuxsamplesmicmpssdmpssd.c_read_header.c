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
struct virtio_blk_outhdr {int dummy; } ;
struct mic_copy_desc {int iovcnt; int update_used; scalar_t__ vr_idx; struct iovec* iov; } ;
struct iovec {int iov_len; struct virtio_blk_outhdr* iov_base; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MIC_VIRTIO_COPY_DESC ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mic_copy_desc*) ; 

__attribute__((used)) static int
read_header(int fd, struct virtio_blk_outhdr *hdr, __u32 desc_idx)
{
	struct iovec iovec;
	struct mic_copy_desc copy;

	iovec.iov_len = sizeof(*hdr);
	iovec.iov_base = hdr;
	copy.iov = &iovec;
	copy.iovcnt = 1;
	copy.vr_idx = 0;  /* only one vring on virtio_block */
	copy.update_used = false;  /* do not update used index */
	return ioctl(fd, MIC_VIRTIO_COPY_DESC, &copy);
}