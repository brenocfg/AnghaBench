#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ion_handle_data {unsigned long arg; int /*<<< orphan*/  handle; int /*<<< orphan*/  member_0; int /*<<< orphan*/  cmd; int /*<<< orphan*/  fd; } ;
struct ion_flush_data {int /*<<< orphan*/  length; scalar_t__ offset; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  handle; int /*<<< orphan*/  member_0; } ;
struct ion_fd_data {unsigned long arg; int /*<<< orphan*/  handle; int /*<<< orphan*/  member_0; int /*<<< orphan*/  cmd; int /*<<< orphan*/  fd; } ;
struct ion_custom_data {unsigned long arg; int /*<<< orphan*/  handle; int /*<<< orphan*/  member_0; int /*<<< orphan*/  cmd; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ VisionBuf ;

/* Variables and functions */
 int /*<<< orphan*/  ION_IOC_CLEAN_CACHES ; 
 int /*<<< orphan*/  ION_IOC_CUSTOM ; 
 int /*<<< orphan*/  ION_IOC_FREE ; 
 int /*<<< orphan*/  ION_IOC_IMPORT ; 
 int /*<<< orphan*/  ION_IOC_INV_CACHES ; 
#define  VISIONBUF_SYNC_FROM_DEVICE 129 
#define  VISIONBUF_SYNC_TO_DEVICE 128 
 int /*<<< orphan*/  assert (int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ion_handle_data*) ; 
 int /*<<< orphan*/  ion_fd ; 

void visionbuf_sync(const VisionBuf* buf, int dir) {
  int err;

  struct ion_fd_data fd_data = {0};
  fd_data.fd = buf->fd;
  err = ioctl(ion_fd, ION_IOC_IMPORT, &fd_data);
  assert(err == 0);

  struct ion_flush_data flush_data = {0};
  flush_data.handle = fd_data.handle;
  flush_data.vaddr = buf->addr;
  flush_data.offset = 0;
  flush_data.length = buf->len;

  // ION_IOC_INV_CACHES ~= DMA_FROM_DEVICE
  // ION_IOC_CLEAN_CACHES ~= DMA_TO_DEVICE
  // ION_IOC_CLEAN_INV_CACHES ~= DMA_BIDIRECTIONAL

  struct ion_custom_data custom_data = {0};

  switch (dir) {
  case VISIONBUF_SYNC_FROM_DEVICE:
    custom_data.cmd = ION_IOC_INV_CACHES;
    break;
  case VISIONBUF_SYNC_TO_DEVICE:
    custom_data.cmd = ION_IOC_CLEAN_CACHES;
    break;
  default:
    assert(0);
  }

  custom_data.arg = (unsigned long)&flush_data;
  err = ioctl(ion_fd, ION_IOC_CUSTOM, &custom_data);
  assert(err == 0);

  struct ion_handle_data handle_data = {0};
  handle_data.handle = fd_data.handle;
  err = ioctl(ion_fd, ION_IOC_FREE, &handle_data);
  assert(err == 0);
}