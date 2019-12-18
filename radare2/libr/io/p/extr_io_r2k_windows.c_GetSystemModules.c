#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int NumberOfModules; TYPE_2__* Modules; } ;
struct TYPE_6__ {int /*<<< orphan*/  ImageBase; int /*<<< orphan*/  ImageSize; scalar_t__ FullPathName; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cb_printf ) (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RIO ;
typedef  TYPE_2__* PRTL_PROCESS_MODULE_INFORMATION ;
typedef  TYPE_3__* PRTL_PROCESS_MODULES ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* GetFileName (char const*) ; 
 int /*<<< orphan*/  IOCTL_GET_SYSTEM_MODULES ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 scalar_t__ gHandleDriver ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  stub1 (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int GetSystemModules(RIO *io) {
	DWORD bRead = 0;
	int i;
	LPVOID lpBufMods = NULL;
	int bufmodsize = 1024 * 1024;
	if(gHandleDriver) {
		if (!(lpBufMods = malloc (bufmodsize))) {
			eprintf ("[r2k] GetSystemModules: Error can't allocate %i bytes of memory.\n", bufmodsize);
			return -1;
		}
		if (DeviceIoControl (gHandleDriver, IOCTL_GET_SYSTEM_MODULES, lpBufMods, bufmodsize, lpBufMods, bufmodsize, &bRead, NULL)) {
			PRTL_PROCESS_MODULES pm = (PRTL_PROCESS_MODULES)lpBufMods;
			PRTL_PROCESS_MODULE_INFORMATION pMod = pm->Modules;
			for (i = 0; i < pm->NumberOfModules; i++) {
				const char *fileName = GetFileName((const char*)pMod[i].FullPathName);
				io->cb_printf ("f nt.%s 0x%x @ 0x%p\n", fileName, pMod[i].ImageSize, pMod[i].ImageBase);
			}
		}
	} else {
		eprintf ("Driver not initialized.\n");
	}
	return 1;
}