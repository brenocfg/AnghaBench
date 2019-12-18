#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t punteroBuffer; int /*<<< orphan*/  hReadPipeIn; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ libbochs_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int O_NONBLOCK ; 
 scalar_t__ PeekNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int SIZE_BUF ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  bochs_reset_buffer (TYPE_1__*) ; 
 int fcntl (int /*<<< orphan*/ ,int,...) ; 
 scalar_t__* lpTmpBuffer ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int read (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ strstr (int /*<<< orphan*/ *,char*) ; 

bool bochs_wait(libbochs_t *b) {
#if __WINDOWS__
	int times = 100;
	DWORD dwRead, aval, leftm;
	bochs_reset_buffer(b);	
	do {
		while (PeekNamedPipe (b->hReadPipeIn, NULL, 0, NULL, &aval, &leftm)) {
			if (aval < 0) break;
			if (!ReadFile (b->hReadPipeIn, &b->data[b->punteroBuffer], SIZE_BUF, &dwRead, 0)) {
				lprintf("bochs_wait: ERROR reading from pipe.\n\n");
				return false;
			}
			if (dwRead)
				b->punteroBuffer +=dwRead;
		}
		if (strstr (b->data, "<bochs:")) {
			break;
		}
		Sleep (5);
	} while (--times);
	return true;
#else
	int flags,n;
	bochs_reset_buffer (b);
	flags = fcntl (b->hReadPipeIn, F_GETFL, 0);
	(void) fcntl (b->hReadPipeIn, (flags | O_NONBLOCK));
	for (;;) {
		n = read (b->hReadPipeIn, lpTmpBuffer, SIZE_BUF - 1);
		if (n > 0) {
			lpTmpBuffer[n] = 0;
			if (b->punteroBuffer + n >= SIZE_BUF - 1) {
				bochs_reset_buffer(b);
			}
			// XXX overflow here
			memcpy (b->data + b->punteroBuffer, lpTmpBuffer, n + 1);
			b->punteroBuffer += n;
			if (strstr (&b->data[0], "<bochs:")) {
				break;
			}
		}
	}
	(void) fcntl (b->hReadPipeIn, (flags | ~O_NONBLOCK));
	return true;
#endif
}