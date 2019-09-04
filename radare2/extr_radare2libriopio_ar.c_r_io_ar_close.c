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
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int ar_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_io_ar_close(RIODesc *fd) {
	RBuffer *b = NULL;
	if (!fd || !fd->data) {
		return -1;
	}
	b = fd->data;
	return ar_close (b);
}