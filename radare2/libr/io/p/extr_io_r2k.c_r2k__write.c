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
 int /*<<< orphan*/  IOCTL_WRITE_KERNEL_MEMORY ; 
 int /*<<< orphan*/  IOCTL_WRITE_PHYSICAL_ADDR ; 
 int /*<<< orphan*/  IOCTL_WRITE_PROCESS_ADDR ; 
 int WriteKernelMemory (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int WriteMemory (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 TYPE_2__ r2k_struct ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 

int r2k__write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
#if __WINDOWS__
	//eprintf("writing to: 0x%"PFMT64x" len: %x\n",io->off, count);
	return WriteKernelMemory (io->off, buf, count);
#elif defined (__linux__) && !defined (__GNU__)
	switch (r2k_struct.beid) {
	case 0:
		return WriteMemory (io, fd, IOCTL_WRITE_KERNEL_MEMORY, r2k_struct.pid, io->off, buf, count);
	case 1:
		return WriteMemory (io, fd, IOCTL_WRITE_PROCESS_ADDR, r2k_struct.pid, io->off, buf, count);
	case 2:
		return WriteMemory (io, fd, IOCTL_WRITE_PHYSICAL_ADDR, r2k_struct.pid, io->off, buf, count);
	default:
		io->cb_printf ("ERROR: Undefined beid in r2k__write.\n");
		return -1;
	}
#else
	io->cb_printf ("TODO: r2k not implemented for this plataform.\n");
	return -1;
#endif
}