#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hWritePipeOut; } ;
typedef  TYPE_1__ libbochs_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bochs_reset_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  bochs_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_newf (char*,char const*) ; 
 size_t strlen (char*) ; 
 size_t write (int /*<<< orphan*/ ,char*,size_t) ; 

void bochs_send_cmd(libbochs_t* b, const char *cmd, bool bWait) {
	char *cmdbuff = r_str_newf ("%s\n", cmd);
	bochs_reset_buffer (b);
#if __WINDOWS__
	{
		DWORD dwWritten;
		WriteFile (b->hWritePipeOut, cmdbuff, strlen (cmdbuff), &dwWritten, NULL);
	}
#else
	size_t cmdlen = strlen (cmdbuff);
	if (write (b->hWritePipeOut, cmdbuff, cmdlen) != cmdlen) {
		eprintf ("boch_send_cmd failed\n");
		goto beach;
	}
#endif
	if (bWait)
		bochs_wait (b);
beach:
	free (cmdbuff);
}