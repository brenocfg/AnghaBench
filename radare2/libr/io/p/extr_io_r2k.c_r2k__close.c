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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  StartStopService (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ gHandleDriver ; 

__attribute__((used)) static int r2k__close(RIODesc *fd) {
#if __WINDOWS__
	if (gHandleDriver) {
		CloseHandle (gHandleDriver);
		StartStopService (TEXT ("r2k"),TRUE);
	}
#elif defined (__linux__) && !defined (__GNU__)
	if (fd) {
		close ((int)(size_t)fd->data);
	}
#else
	eprintf ("TODO: r2k not implemented for this plataform.\n");
#endif
	return 0;
}