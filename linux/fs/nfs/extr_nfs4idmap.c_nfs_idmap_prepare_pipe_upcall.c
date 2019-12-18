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
struct idmap_legacy_upcalldata {int dummy; } ;
struct idmap {struct idmap_legacy_upcalldata* idmap_upcall_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static bool
nfs_idmap_prepare_pipe_upcall(struct idmap *idmap,
		struct idmap_legacy_upcalldata *data)
{
	if (idmap->idmap_upcall_data != NULL) {
		WARN_ON_ONCE(1);
		return false;
	}
	idmap->idmap_upcall_data = data;
	return true;
}