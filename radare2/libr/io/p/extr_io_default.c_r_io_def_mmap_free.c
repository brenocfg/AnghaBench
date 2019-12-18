#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  buf; struct TYPE_4__* filename; } ;
typedef  TYPE_1__ RIOMMapFileObj ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_io_def_mmap_free (RIOMMapFileObj *mmo) {
	if (mmo) {
		free (mmo->filename);
		r_buf_free (mmo->buf);
		close (mmo->fd);
		free (mmo);
	}
}