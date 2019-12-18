#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  b; struct TYPE_5__* password; struct TYPE_5__* name; scalar_t__ modified; } ;
typedef  TYPE_1__ RIOZipFileObj ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_zip_flush_file (TYPE_1__*) ; 

__attribute__((used)) static void r_io_zip_free_zipfileobj(RIOZipFileObj *zfo) {
	if (!zfo) {
		return;
	}
	if (zfo->modified) {
		r_io_zip_flush_file (zfo);
	}
	free (zfo->name);
	free (zfo->password);
	r_buf_free (zfo->b);
	free (zfo);
}