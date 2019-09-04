#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int wp; scalar_t__ pid; scalar_t__ beid; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cb_printf ) (char*) ;} ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int R_PERM_WX ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ r2k_struct ; 
 int /*<<< orphan*/ * r_io_desc_new (TYPE_1__*,int /*<<< orphan*/ *,char const*,int,int,void*) ; 
 int /*<<< orphan*/  r_io_plugin_r2k ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static RIODesc *r2k__open(RIO *io, const char *pathname, int rw, int mode) {
	if (!strncmp (pathname, "r2k://", 6)) {
		rw |= R_PERM_WX;
#if __WINDOWS__
		RIOW32 *w32 = R_NEW0 (RIOW32);
		if (Init (&pathname[6]) == FALSE) {
			eprintf ("r2k__open: Error cant init driver: %s\n", &pathname[6]);
			free (w32);
			return NULL;
		}
		//return r_io_desc_new (&r_io_plugin_r2k, -1, pathname, rw, mode, w32);
		return r_io_desc_new (io, &r_io_plugin_r2k, pathname, rw, mode, w32);
#elif defined (__linux__) && !defined (__GNU__)
		int fd = open ("/dev/r2k", O_RDONLY);
		if (fd == -1) {
			io->cb_printf ("r2k__open: Error in opening /dev/r2k.");
			return NULL;
		}

		r2k_struct.beid = 0;
		r2k_struct.pid = 0;
		r2k_struct.wp = 1;
		return r_io_desc_new (io, &r_io_plugin_r2k, pathname, rw, mode, (void *)(size_t)fd);
#else
		io->cb_printf ("Not supported on this platform\n");
#endif
	}
	return NULL;
}