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
struct TYPE_6__ {struct TYPE_6__* buf; int /*<<< orphan*/  bfvm; } ;
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIOBfdbg ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  bfvm_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __close(RIODesc *fd) {
	RIOBfdbg *riom;
	if (!fd || !fd->data) {
		return -1;
	}
	riom = fd->data;
	bfvm_free (riom->bfvm);
	R_FREE (riom->buf);
	R_FREE (fd->data);
	return 0;
}