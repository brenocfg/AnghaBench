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
typedef  int /*<<< orphan*/  uuid_t ;
struct TYPE_4__ {scalar_t__ index; int /*<<< orphan*/  nfs_export; } ;
struct ovl_fs {unsigned int numlowerfs; TYPE_3__* lower_fs; scalar_t__ upper_mnt; TYPE_1__ config; } ;
struct TYPE_6__ {TYPE_2__* sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_uuid; } ;

/* Variables and functions */
 scalar_t__ uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool ovl_lower_uuid_ok(struct ovl_fs *ofs, const uuid_t *uuid)
{
	unsigned int i;

	if (!ofs->config.nfs_export && !(ofs->config.index && ofs->upper_mnt))
		return true;

	for (i = 0; i < ofs->numlowerfs; i++) {
		/*
		 * We use uuid to associate an overlay lower file handle with a
		 * lower layer, so we can accept lower fs with null uuid as long
		 * as all lower layers with null uuid are on the same fs.
		 */
		if (uuid_equal(&ofs->lower_fs[i].sb->s_uuid, uuid))
			return false;
	}
	return true;
}