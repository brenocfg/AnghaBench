#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct rproc_vdev {int rsc_offset; int /*<<< orphan*/ * vring; TYPE_1__ subdev; int /*<<< orphan*/  node; struct rproc* rproc; int /*<<< orphan*/  id; int /*<<< orphan*/  refcount; } ;
struct device {int dummy; } ;
struct rproc {int /*<<< orphan*/  rvdevs; struct device dev; } ;
struct fw_rsc_vdev_vring {int dummy; } ;
struct fw_rsc_vdev {int num_of_vrings; int /*<<< orphan*/  id; int /*<<< orphan*/  config_len; int /*<<< orphan*/  dfeatures; scalar_t__* reserved; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct rproc_vdev*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct rproc_vdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_add_subdev (struct rproc*,TYPE_1__*) ; 
 int rproc_alloc_vring (struct rproc_vdev*,int) ; 
 int /*<<< orphan*/  rproc_free_vring (int /*<<< orphan*/ *) ; 
 int rproc_parse_vring (struct rproc_vdev*,struct fw_rsc_vdev*,int) ; 
 int /*<<< orphan*/  rproc_vdev_do_start ; 
 int /*<<< orphan*/  rproc_vdev_do_stop ; 

__attribute__((used)) static int rproc_handle_vdev(struct rproc *rproc, struct fw_rsc_vdev *rsc,
			     int offset, int avail)
{
	struct device *dev = &rproc->dev;
	struct rproc_vdev *rvdev;
	int i, ret;

	/* make sure resource isn't truncated */
	if (sizeof(*rsc) + rsc->num_of_vrings * sizeof(struct fw_rsc_vdev_vring)
			+ rsc->config_len > avail) {
		dev_err(dev, "vdev rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved[0] || rsc->reserved[1]) {
		dev_err(dev, "vdev rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	dev_dbg(dev, "vdev rsc: id %d, dfeatures 0x%x, cfg len %d, %d vrings\n",
		rsc->id, rsc->dfeatures, rsc->config_len, rsc->num_of_vrings);

	/* we currently support only two vrings per rvdev */
	if (rsc->num_of_vrings > ARRAY_SIZE(rvdev->vring)) {
		dev_err(dev, "too many vrings: %d\n", rsc->num_of_vrings);
		return -EINVAL;
	}

	rvdev = kzalloc(sizeof(*rvdev), GFP_KERNEL);
	if (!rvdev)
		return -ENOMEM;

	kref_init(&rvdev->refcount);

	rvdev->id = rsc->id;
	rvdev->rproc = rproc;

	/* parse the vrings */
	for (i = 0; i < rsc->num_of_vrings; i++) {
		ret = rproc_parse_vring(rvdev, rsc, i);
		if (ret)
			goto free_rvdev;
	}

	/* remember the resource offset*/
	rvdev->rsc_offset = offset;

	/* allocate the vring resources */
	for (i = 0; i < rsc->num_of_vrings; i++) {
		ret = rproc_alloc_vring(rvdev, i);
		if (ret)
			goto unwind_vring_allocations;
	}

	list_add_tail(&rvdev->node, &rproc->rvdevs);

	rvdev->subdev.start = rproc_vdev_do_start;
	rvdev->subdev.stop = rproc_vdev_do_stop;

	rproc_add_subdev(rproc, &rvdev->subdev);

	return 0;

unwind_vring_allocations:
	for (i--; i >= 0; i--)
		rproc_free_vring(&rvdev->vring[i]);
free_rvdev:
	kfree(rvdev);
	return ret;
}