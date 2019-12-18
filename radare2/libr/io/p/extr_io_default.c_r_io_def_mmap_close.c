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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  RIOMMapFileObj ;
typedef  TYPE_1__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  r_io_def_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 

__attribute__((used)) static int r_io_def_mmap_close(RIODesc *fd) {
	r_return_val_if_fail (fd && fd->data, -1);
	r_io_def_mmap_free ((RIOMMapFileObj *) fd->data);
	fd->data = NULL;
	return 0;
}