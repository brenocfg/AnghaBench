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
struct gport {int fd; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_OVERLAPPED (int /*<<< orphan*/ ) ; 
 scalar_t__ CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int close (int) ; 
 int /*<<< orphan*/  read_ovl ; 
 int /*<<< orphan*/  wait_ovl ; 
 int /*<<< orphan*/  write_ovl ; 

__attribute__((used)) static int sp_close(struct gport *port) {
#if __WINDOWS__
	/* Returns non-zero upon success, 0 upon failure. */
	if (CloseHandle (port->hdl) == 0){
		return -1;
	}
	port->hdl = INVALID_HANDLE_VALUE;

	/* Close event handles for overlapped structures. */
#define CLOSE_OVERLAPPED(ovl)                                   \
	do {                                                    \
		if (port->ovl.hEvent != INVALID_HANDLE_VALUE && \
			CloseHandle (port->ovl.hEvent) == 0)    \
			return -1;                              \
	} while (0)
	CLOSE_OVERLAPPED (read_ovl);
	CLOSE_OVERLAPPED (write_ovl);
	CLOSE_OVERLAPPED (wait_ovl);
#else
	if (close (port->fd) == -1) {
		return -1;
	}

	port->fd = -1;
#endif
	return 0;
}