#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _SECURITY_ATTRIBUTES {int nLength; int bInheritHandle; scalar_t__ lpSecurityDescriptor; } ;
struct TYPE_10__ {int cb; int hStdError; int hStdOutput; int hStdInput; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_9__ {int hReadPipeIn; int hReadPipeOut; int hWritePipeIn; int hWritePipeOut; int isRunning; int pid; TYPE_2__ processInfo; TYPE_2__ info; void* data; } ;
typedef  TYPE_1__ libbochs_t ;
typedef  int /*<<< orphan*/  commandline ;
typedef  int /*<<< orphan*/  STARTUPINFOA ;
typedef  int /*<<< orphan*/  PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW_CONSOLE ; 
 scalar_t__ CreatePipe (int*,int*,struct _SECURITY_ATTRIBUTES*,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 size_t PIPE_READ ; 
 size_t PIPE_WRITE ; 
 int /*<<< orphan*/  R_FREE (void*) ; 
 int /*<<< orphan*/  SIZE_BUF ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitForInputIdle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bochs_close (TYPE_1__*) ; 
 int /*<<< orphan*/  bochs_reset_buffer (TYPE_1__*) ; 
 scalar_t__ bochs_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  execl (char const*,char const*,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 void* lpTmpBuffer ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  r_sys_conv_utf8_to_win (char*) ; 
 int read (int,void*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

bool bochs_open(libbochs_t* b, const char * pathBochs, const char * pathConfig) {
	bool result = false;

	b->data = malloc (SIZE_BUF);
	if (!b->data) {
		return false;
	}
	lpTmpBuffer = malloc (SIZE_BUF);
	if (!lpTmpBuffer) {
		R_FREE (b->data);
		return false;
	}
#if __WINDOWS__
	struct _SECURITY_ATTRIBUTES PipeAttributes;
	char commandline[1024];
	PipeAttributes.nLength = 12;
	PipeAttributes.bInheritHandle = 1;
	PipeAttributes.lpSecurityDescriptor = 0;
	//
	if (CreatePipe (&b->hReadPipeIn, &b->hReadPipeOut, &PipeAttributes, SIZE_BUF) &&
	    CreatePipe (&b->hWritePipeIn, &b->hWritePipeOut, &PipeAttributes, SIZE_BUF)
	   ) {
		LPTSTR commandline_;

		memset (&b->info, 0, sizeof (STARTUPINFOA));
		memset (&b->processInfo, 0, sizeof (PROCESS_INFORMATION));
		b->info.cb = sizeof (STARTUPINFOA);
		b->info.hStdError = b->hReadPipeOut;
		b->info.hStdOutput = b->hReadPipeOut;
		b->info.hStdInput = b->hWritePipeIn;
		b->info.dwFlags |=  STARTF_USESTDHANDLES;
		snprintf (commandline, sizeof (commandline), "\"%s\" -f \"%s\" -q ", pathBochs, pathConfig);
		lprintf ("*** Creating process: %s\n", commandline);
		commandline_ = r_sys_conv_utf8_to_win (commandline);
		if (CreateProcess (NULL, commandline_, NULL, NULL, TRUE, CREATE_NEW_CONSOLE,
				NULL, NULL, &b->info, &b->processInfo)) {
			lprintf ("Process created\n");
			WaitForInputIdle (b->processInfo.hProcess, INFINITE);
			lprintf ("Initialized input\n");
			b->isRunning = true;
			bochs_reset_buffer (b);
			eprintf ("Waiting for bochs...\n");
			if (bochs_wait (b)) {
				eprintf ("Ready.\n");
				result = true;
			} else {
				bochs_close (b);
			}
		}
		free (commandline_);
	}
#else
	#define PIPE_READ 0
	#define PIPE_WRITE 1
	int aStdinPipe[2];
	int aStdoutPipe[2];
	int nChild;

	if (pipe (aStdinPipe) < 0) {
		eprintf ("Error: allocating pipe for child input redirect");
		return false;
	}
	if (pipe(aStdoutPipe) < 0) {
		close (aStdinPipe[PIPE_READ]);
		close (aStdinPipe[PIPE_WRITE]);
		eprintf ("Error: allocating pipe for child output redirect");
		return false;
	}

	nChild = fork ();
	if (0 == nChild) {
		// redirect stdin
		if (dup2 (aStdinPipe[PIPE_READ], STDIN_FILENO) == -1) {
			eprintf ("Error: redirecting stdin");
			return false;
		}

		// redirect stdout
		if (dup2 (aStdoutPipe[PIPE_WRITE], STDOUT_FILENO) == -1) {
			eprintf ("Error: redirecting stdout");
			return false;
		}

		// redirect stderr
		if (dup2 (aStdoutPipe[PIPE_WRITE], STDERR_FILENO) == -1) {
			eprintf ("Error: redirecting stderr");
			return false;
		}

		close (aStdinPipe[PIPE_READ]);
		close (aStdinPipe[PIPE_WRITE]);
		close (aStdoutPipe[PIPE_READ]);
		close (aStdoutPipe[PIPE_WRITE]);
		(void) execl (pathBochs, pathBochs, "-q", "-f", pathConfig, NULL);
		perror ("execl");
		exit (1);
	} else if (nChild > 0) {
		close (aStdinPipe[PIPE_READ]);
		close (aStdoutPipe[PIPE_WRITE]);

		if (read (aStdoutPipe[PIPE_READ], lpTmpBuffer, 1) != 1) {
			eprintf ("boch_open failed");
			bochs_close (b);
		} else {
			b->hReadPipeIn  = aStdoutPipe[PIPE_READ];
			b->hWritePipeOut = aStdinPipe[PIPE_WRITE];
			b->isRunning = true;
			bochs_reset_buffer (b);
			eprintf ("Waiting for bochs...\n");
			if (bochs_wait (b)) {
				eprintf ("Ready.\n");
				b->pid = nChild;
				result = true;
			} else {
				bochs_close (b);
			}
		}
	} else {
		perror ("pipe");
		// failed to create child
		close (aStdinPipe[PIPE_READ]);
		close (aStdinPipe[PIPE_WRITE]);
		close (aStdoutPipe[PIPE_READ]);
		close (aStdoutPipe[PIPE_WRITE]);
	}
#endif
	return result;
}