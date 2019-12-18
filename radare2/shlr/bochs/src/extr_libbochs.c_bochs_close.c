#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_5__ {int isRunning; int /*<<< orphan*/  data; int /*<<< orphan*/  pid; int /*<<< orphan*/  hWritePipeOut; int /*<<< orphan*/  hReadPipeIn; TYPE_1__ processInfo; int /*<<< orphan*/  ghWriteEvent; int /*<<< orphan*/  hWritePipeIn; int /*<<< orphan*/  hReadPipeOut; } ;
typedef  TYPE_2__ libbochs_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpTmpBuffer ; 

void bochs_close(libbochs_t* b) {
	b->isRunning = false;
#if __WINDOWS__
	CloseHandle (b->hReadPipeIn);
	CloseHandle (b->hReadPipeOut);
	CloseHandle (b->hWritePipeIn);
	CloseHandle (b->hWritePipeOut);
	CloseHandle (b->ghWriteEvent);
	TerminateProcess (b->processInfo.hProcess,0);
	free (b->data);
	free (lpTmpBuffer);
#else
	close (b->hReadPipeIn);
	close (b->hWritePipeOut);
	kill (b->pid, SIGKILL);
	R_FREE (b->data);
	R_FREE (lpTmpBuffer);
#endif
}