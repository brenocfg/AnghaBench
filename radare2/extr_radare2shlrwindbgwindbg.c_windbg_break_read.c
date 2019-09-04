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

/* Variables and functions */

int windbg_break_read(WindCtx *ctx) {
#if __WINDOWS__ && !defined(_MSC_VER)
	static BOOL WINAPI (*w32_CancelIoEx)(HANDLE, LPOVERLAPPED) = NULL;
	if (!w32_CancelIoEx) {
		w32_CancelIoEx = (BOOL WINAPI (*)(HANDLE, LPOVERLAPPED))
				 GetProcAddress (GetModuleHandle (TEXT ("kernel32")),
			"CancelIoEx");
	}
	if (w32_CancelIoEx) {
		w32_CancelIoEx (ctx->io_ptr, NULL);
	}
#endif
	return 1;
}