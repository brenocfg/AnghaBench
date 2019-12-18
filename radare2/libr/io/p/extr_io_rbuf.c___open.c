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
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new () ; 
 int /*<<< orphan*/ * r_io_desc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_plugin_rbuf ; 

__attribute__((used)) static RIODesc *__open(RIO *io, const char *pathname, int rw, int mode) {
	RIODesc *desc;
	RBuffer *buf = r_buf_new ();
	if (buf && (desc = r_io_desc_new (io, &r_io_plugin_rbuf, pathname, 7, 0, buf))) {
		return desc;
	}
	r_buf_free (buf);
	return NULL;
}