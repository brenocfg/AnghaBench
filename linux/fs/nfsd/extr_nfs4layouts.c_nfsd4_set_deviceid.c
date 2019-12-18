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
typedef  int /*<<< orphan*/  u32 ;
struct svc_fh {TYPE_2__* fh_export; } ;
struct nfsd4_deviceid {scalar_t__ pad; int /*<<< orphan*/  generation; int /*<<< orphan*/  fsid_idx; } ;
struct TYPE_4__ {TYPE_1__* ex_devid_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  nfsd4_alloc_devid_map (struct svc_fh const*) ; 

int
nfsd4_set_deviceid(struct nfsd4_deviceid *id, const struct svc_fh *fhp,
		u32 device_generation)
{
	if (!fhp->fh_export->ex_devid_map) {
		nfsd4_alloc_devid_map(fhp);
		if (!fhp->fh_export->ex_devid_map)
			return -ENOMEM;
	}

	id->fsid_idx = fhp->fh_export->ex_devid_map->idx;
	id->generation = device_generation;
	id->pad = 0;
	return 0;
}