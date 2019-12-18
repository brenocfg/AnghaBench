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
typedef  int /*<<< orphan*/  WindCtx ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  __plugin_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 void* iob_open (char const*) ; 
 int /*<<< orphan*/  iob_select (char*) ; 
 int /*<<< orphan*/ * r_io_desc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_plugin_windbg ; 
 int /*<<< orphan*/ * windbg_ctx_new (void*) ; 

__attribute__((used)) static RIODesc *__open(RIO *io, const char *file, int rw, int mode) {
	if (!__plugin_open (io, file, 0)) {
		return NULL;
	}

	if (!iob_select ("pipe")) {
		eprintf("Could not initialize the IO backend\n");
		return NULL;
	}

	void *io_ctx = iob_open (file + 9);
	if (!io_ctx) {
		eprintf ("Could not open the pipe\n");
		return NULL;
	}
	eprintf ("Opened pipe %s with fd %p\n", file + 9, io_ctx);

	WindCtx *ctx = windbg_ctx_new (io_ctx);
	if (!ctx) {
		eprintf ("Failed to initialize windbg context\n");
		return NULL;
	}
	return r_io_desc_new (io, &r_io_plugin_windbg, file, rw, mode, ctx);
}