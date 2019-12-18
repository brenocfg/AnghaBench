#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/  buffer; TYPE_1__ address; } ;
typedef  TYPE_2__* PPA ;
typedef  int /*<<< orphan*/  PA ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOCTL_WRITE_KERNEL_MEM ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ gHandleDriver ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int WriteKernelMemory (ut64 address, const ut8 *buf, int len) {
	DWORD ret = -1, bRead = 0;
	LPVOID lpBuffer = NULL;
	int bufsize;
	PPA p;
	if(gHandleDriver) {
		bufsize = sizeof (PA) + len;
		if (!(lpBuffer = malloc (bufsize))) {
			eprintf ("[r2k] WriteKernelMemory: Error can't allocate %i bytes of memory.\n", bufsize);
			return -1;
		}
		p = (PPA)lpBuffer;
		p->address.QuadPart = address;
		p->len = len;
		memcpy (&p->buffer, buf, len);
		if (DeviceIoControl (gHandleDriver, IOCTL_WRITE_KERNEL_MEM, lpBuffer, bufsize, lpBuffer, bufsize, &bRead, NULL)) {
			ret = len;
		} else {
			eprintf ("[r2k] WriteKernelMemory: Error IOCTL_WRITE_KERNEL_MEM.\n");
			ret = -1;
		}
		free (lpBuffer);
	} else {
		eprintf ("Driver not initialized.\n");
	}
	return ret;
}