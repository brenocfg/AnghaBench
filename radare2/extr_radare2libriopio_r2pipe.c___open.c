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
typedef  int /*<<< orphan*/  R2Pipe ;

/* Variables and functions */
 scalar_t__ __check (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r2pipe_open (char const*) ; 
 int /*<<< orphan*/ * r_io_desc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_plugin_r2pipe ; 

__attribute__((used)) static RIODesc *__open(RIO *io, const char *pathname, int rw, int mode) {
	R2Pipe *r2p = NULL;
	if (__check (io, pathname, 0)) {
		r2p = r2pipe_open (pathname + 9);
	}
	return r2p? r_io_desc_new (io, &r_io_plugin_r2pipe,
		pathname, rw, mode, r2p): NULL;
}