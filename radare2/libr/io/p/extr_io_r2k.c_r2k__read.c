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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_6__ {int beid; int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cb_printf ) (char*) ;int /*<<< orphan*/  off; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_READ_KERNEL_MEMORY ; 
 int /*<<< orphan*/  IOCTL_READ_PHYSICAL_ADDR ; 
 int /*<<< orphan*/  IOCTL_READ_PROCESS_ADDR ; 
 int ReadKernelMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ReadMemory (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__ r2k_struct ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 

__attribute__((used)) static int r2k__read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
#if __WINDOWS__
	return ReadKernelMemory (io->off, buf, count);
#elif defined (__linux__) && !defined (__GNU__)
	switch (r2k_struct.beid) {
	case 0:
		return ReadMemory (io, fd, IOCTL_READ_KERNEL_MEMORY, r2k_struct.pid, io->off, buf, count);
	case 1:
		return ReadMemory (io, fd, IOCTL_READ_PROCESS_ADDR, r2k_struct.pid, io->off, buf, count);
	case 2:
		return ReadMemory (io, fd, IOCTL_READ_PHYSICAL_ADDR, r2k_struct.pid, io->off, buf, count);
	default:
		io->cb_printf ("ERROR: Undefined beid in r2k__read.\n");
		memset (buf, 0xff, count);
		return count;
	}
#else
	io->cb_printf ("TODO: r2k not implemented for this plataform.\n");
	memset (buf, 0xff, count);
	return count;
#endif
}