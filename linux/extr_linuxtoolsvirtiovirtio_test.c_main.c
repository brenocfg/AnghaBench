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
struct vdev_info {int /*<<< orphan*/ * vqs; } ;

/* Variables and functions */
 unsigned long long VIRTIO_F_VERSION_1 ; 
 unsigned long long VIRTIO_RING_F_EVENT_IDX ; 
 unsigned long long VIRTIO_RING_F_INDIRECT_DESC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  longopts ; 
 int /*<<< orphan*/  optstring ; 
 int /*<<< orphan*/  run_test (struct vdev_info*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vdev_info_init (struct vdev_info*,unsigned long long) ; 
 int /*<<< orphan*/  vq_info_add (struct vdev_info*,int) ; 

int main(int argc, char **argv)
{
	struct vdev_info dev;
	unsigned long long features = (1ULL << VIRTIO_RING_F_INDIRECT_DESC) |
		(1ULL << VIRTIO_RING_F_EVENT_IDX) | (1ULL << VIRTIO_F_VERSION_1);
	int o;
	bool delayed = false;

	for (;;) {
		o = getopt_long(argc, argv, optstring, longopts, NULL);
		switch (o) {
		case -1:
			goto done;
		case '?':
			help();
			exit(2);
		case 'e':
			features &= ~(1ULL << VIRTIO_RING_F_EVENT_IDX);
			break;
		case 'h':
			help();
			goto done;
		case 'i':
			features &= ~(1ULL << VIRTIO_RING_F_INDIRECT_DESC);
			break;
		case '0':
			features &= ~(1ULL << VIRTIO_F_VERSION_1);
			break;
		case 'D':
			delayed = true;
			break;
		default:
			assert(0);
			break;
		}
	}

done:
	vdev_info_init(&dev, features);
	vq_info_add(&dev, 256);
	run_test(&dev, &dev.vqs[0], delayed, 0x100000);
	return 0;
}