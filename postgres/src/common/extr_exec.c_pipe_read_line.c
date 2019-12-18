#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  pi ;
struct TYPE_3__ {int nLength; int /*<<< orphan*/ * lpSecurityDescriptor; int /*<<< orphan*/  bInheritHandle; } ;
typedef  char STARTUPINFO ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  char PROCESS_INFORMATION ;
typedef  void* HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (void*) ; 
 int /*<<< orphan*/  CreatePipe (void**,void**,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateProcess (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ReadFile (void*,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (void*,int) ; 
 int /*<<< orphan*/  ZeroMemory (char*,int) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 scalar_t__ pclose_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
pipe_read_line(char *cmd, char *line, int maxsize)
{
#ifndef WIN32
	FILE	   *pgver;

	/* flush output buffers in case popen does not... */
	fflush(stdout);
	fflush(stderr);

	errno = 0;
	if ((pgver = popen(cmd, "r")) == NULL)
	{
		perror("popen failure");
		return NULL;
	}

	errno = 0;
	if (fgets(line, maxsize, pgver) == NULL)
	{
		if (feof(pgver))
			fprintf(stderr, "no data was returned by command \"%s\"\n", cmd);
		else
			perror("fgets failure");
		pclose(pgver);			/* no error checking */
		return NULL;
	}

	if (pclose_check(pgver))
		return NULL;

	return line;
#else							/* WIN32 */

	SECURITY_ATTRIBUTES sattr;
	HANDLE		childstdoutrd,
				childstdoutwr,
				childstdoutrddup;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	char	   *retval = NULL;

	sattr.nLength = sizeof(SECURITY_ATTRIBUTES);
	sattr.bInheritHandle = TRUE;
	sattr.lpSecurityDescriptor = NULL;

	if (!CreatePipe(&childstdoutrd, &childstdoutwr, &sattr, 0))
		return NULL;

	if (!DuplicateHandle(GetCurrentProcess(),
						 childstdoutrd,
						 GetCurrentProcess(),
						 &childstdoutrddup,
						 0,
						 FALSE,
						 DUPLICATE_SAME_ACCESS))
	{
		CloseHandle(childstdoutrd);
		CloseHandle(childstdoutwr);
		return NULL;
	}

	CloseHandle(childstdoutrd);

	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdError = childstdoutwr;
	si.hStdOutput = childstdoutwr;
	si.hStdInput = INVALID_HANDLE_VALUE;

	if (CreateProcess(NULL,
					  cmd,
					  NULL,
					  NULL,
					  TRUE,
					  0,
					  NULL,
					  NULL,
					  &si,
					  &pi))
	{
		/* Successfully started the process */
		char	   *lineptr;

		ZeroMemory(line, maxsize);

		/* Try to read at least one line from the pipe */
		/* This may require more than one wait/read attempt */
		for (lineptr = line; lineptr < line + maxsize - 1;)
		{
			DWORD		bytesread = 0;

			/* Let's see if we can read */
			if (WaitForSingleObject(childstdoutrddup, 10000) != WAIT_OBJECT_0)
				break;			/* Timeout, but perhaps we got a line already */

			if (!ReadFile(childstdoutrddup, lineptr, maxsize - (lineptr - line),
						  &bytesread, NULL))
				break;			/* Error, but perhaps we got a line already */

			lineptr += strlen(lineptr);

			if (!bytesread)
				break;			/* EOF */

			if (strchr(line, '\n'))
				break;			/* One or more lines read */
		}

		if (lineptr != line)
		{
			/* OK, we read some data */
			int			len;

			/* If we got more than one line, cut off after the first \n */
			lineptr = strchr(line, '\n');
			if (lineptr)
				*(lineptr + 1) = '\0';

			len = strlen(line);

			/*
			 * If EOL is \r\n, convert to just \n. Because stdout is a
			 * text-mode stream, the \n output by the child process is
			 * received as \r\n, so we convert it to \n.  The server main.c
			 * sets setvbuf(stdout, NULL, _IONBF, 0) which has the effect of
			 * disabling \n to \r\n expansion for stdout.
			 */
			if (len >= 2 && line[len - 2] == '\r' && line[len - 1] == '\n')
			{
				line[len - 2] = '\n';
				line[len - 1] = '\0';
				len--;
			}

			/*
			 * We emulate fgets() behaviour. So if there is no newline at the
			 * end, we add one...
			 */
			if (len == 0 || line[len - 1] != '\n')
				strcat(line, "\n");

			retval = line;
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	CloseHandle(childstdoutwr);
	CloseHandle(childstdoutrddup);

	return retval;
#endif							/* WIN32 */
}