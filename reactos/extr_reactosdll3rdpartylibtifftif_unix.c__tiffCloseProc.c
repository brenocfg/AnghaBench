#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ fd_as_handle_union_t ;

/* Variables and functions */
 int close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_tiffCloseProc(thandle_t fd)
{
	fd_as_handle_union_t fdh;
	fdh.h = fd;
	return(close(fdh.fd));
}