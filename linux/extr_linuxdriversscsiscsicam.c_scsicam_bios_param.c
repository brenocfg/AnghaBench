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
typedef  unsigned long long u64 ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* scsi_bios_ptable (struct block_device*) ; 
 int scsi_partsize (unsigned char*,unsigned long,unsigned int*,unsigned int*,unsigned int*) ; 
 int setsize (unsigned long,unsigned int*,unsigned int*,unsigned int*) ; 

int scsicam_bios_param(struct block_device *bdev, sector_t capacity, int *ip)
{
	unsigned char *p;
	u64 capacity64 = capacity;	/* Suppress gcc warning */
	int ret;

	p = scsi_bios_ptable(bdev);
	if (!p)
		return -1;

	/* try to infer mapping from partition table */
	ret = scsi_partsize(p, (unsigned long)capacity, (unsigned int *)ip + 2,
			       (unsigned int *)ip + 0, (unsigned int *)ip + 1);
	kfree(p);

	if (ret == -1 && capacity64 < (1ULL << 32)) {
		/* pick some standard mapping with at most 1024 cylinders,
		   and at most 62 sectors per track - this works up to
		   7905 MB */
		ret = setsize((unsigned long)capacity, (unsigned int *)ip + 2,
		       (unsigned int *)ip + 0, (unsigned int *)ip + 1);
	}

	/* if something went wrong, then apparently we have to return
	   a geometry with more than 1024 cylinders */
	if (ret || ip[0] > 255 || ip[1] > 63) {
		if ((capacity >> 11) > 65534) {
			ip[0] = 255;
			ip[1] = 63;
		} else {
			ip[0] = 64;
			ip[1] = 32;
		}

		if (capacity > 65535*63*255)
			ip[2] = 65535;
		else
			ip[2] = (unsigned long)capacity / (ip[0] * ip[1]);
	}

	return 0;
}