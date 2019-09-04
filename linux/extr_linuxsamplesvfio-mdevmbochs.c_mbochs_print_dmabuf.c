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
typedef  int u32 ;
struct TYPE_3__ {int drm_format; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mbochs_dmabuf {int /*<<< orphan*/  pagecount; TYPE_1__ mode; int /*<<< orphan*/  id; TYPE_2__* mdev_state; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* mdev_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mbochs_print_dmabuf(struct mbochs_dmabuf *dmabuf,
				const char *prefix)
{
	struct device *dev = mdev_dev(dmabuf->mdev_state->mdev);
	u32 fourcc = dmabuf->mode.drm_format;

	dev_dbg(dev, "%s/%d: %c%c%c%c, %dx%d, stride %d, off 0x%llx, size 0x%llx, pages %ld\n",
		prefix, dmabuf->id,
		fourcc ? ((fourcc >>  0) & 0xff) : '-',
		fourcc ? ((fourcc >>  8) & 0xff) : '-',
		fourcc ? ((fourcc >> 16) & 0xff) : '-',
		fourcc ? ((fourcc >> 24) & 0xff) : '-',
		dmabuf->mode.width, dmabuf->mode.height, dmabuf->mode.stride,
		dmabuf->mode.offset, dmabuf->mode.size, dmabuf->pagecount);
}