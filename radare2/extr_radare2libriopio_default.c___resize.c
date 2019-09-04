#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int perm; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int R_PERM_W ; 
 int r_io_def_mmap_truncate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool __resize(RIO *io, RIODesc *fd, ut64 size) {
	r_return_val_if_fail (io && fd && fd->data, false);
	RIOMMapFileObj *mmo = fd->data;
	if (!(mmo->perm & R_PERM_W)) {
		return false;
	}
	return r_io_def_mmap_truncate (mmo, size);
}