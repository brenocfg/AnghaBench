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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  IsWindows7SP1OrGreater () ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int SEM_FAILCRITICALERRORS ; 
 int SEM_NOGPFAULTERRORBOX ; 
 int /*<<< orphan*/  SetErrorMode (int) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  _set_FMA3_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_spinlock ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_stderr (char*,char const*,int) ; 

__attribute__((used)) static void
startup_hacks(const char *progname)
{
	/*
	 * Windows-specific execution environment hacking.
	 */
#ifdef WIN32
	{
		WSADATA		wsaData;
		int			err;

		/* Make output streams unbuffered by default */
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);

		/* Prepare Winsock */
		err = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (err != 0)
		{
			write_stderr("%s: WSAStartup failed: %d\n",
						 progname, err);
			exit(1);
		}

		/* In case of general protection fault, don't show GUI popup box */
		SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

#if defined(_M_AMD64) && _MSC_VER == 1800

		/*----------
		 * Avoid crashing in certain floating-point operations if we were
		 * compiled for x64 with MS Visual Studio 2013 and are running on
		 * Windows prior to 7/2008R2 SP1 on an AVX2-capable CPU.
		 *
		 * Ref: https://connect.microsoft.com/VisualStudio/feedback/details/811093/visual-studio-2013-rtm-c-x64-code-generation-bug-for-avx2-instructions
		 *----------
		 */
		if (!IsWindows7SP1OrGreater())
		{
			_set_FMA3_enable(0);
		}
#endif							/* defined(_M_AMD64) && _MSC_VER == 1800 */

	}
#endif							/* WIN32 */

	/*
	 * Initialize dummy_spinlock, in case we are on a platform where we have
	 * to use the fallback implementation of pg_memory_barrier().
	 */
	SpinLockInit(&dummy_spinlock);
}