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
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rbuf; } ;
typedef  TYPE_1__ Rihex ;
typedef  TYPE_2__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __close(RIODesc *fd) {
	if (!fd || !fd->data) {
		return -1;
	}
	Rihex *rih = fd->data;
	r_buf_free (rih->rbuf);
	free (rih);
	fd->data = NULL;
	return 0;
}