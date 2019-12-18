#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union pstun {scalar_t__ pst_command; } ;
struct TYPE_2__ {int ps_nargvstr; scalar_t__ ps_argvstr; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  MemSet (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int MyProcPid ; 
 int /*<<< orphan*/  PSTAT_SETCMD ; 
 int /*<<< orphan*/  PS_BUFFER_SIZE ; 
 int /*<<< orphan*/  PS_PADDING ; 
 TYPE_1__* PS_STRINGS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ last_status_len ; 
 scalar_t__ ps_buffer ; 
 scalar_t__ ps_buffer_cur_len ; 
 scalar_t__ ps_buffer_fixed_size ; 
 scalar_t__ ps_buffer_size ; 
 int /*<<< orphan*/  pstat (int /*<<< orphan*/ ,union pstun,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setproctitle (char*,scalar_t__) ; 
 int /*<<< orphan*/  setproctitle_fast (char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__,char const*,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  update_process_title ; 

void
set_ps_display(const char *activity, bool force)
{
#ifndef PS_USE_NONE
	/* update_process_title=off disables updates, unless force = true */
	if (!force && !update_process_title)
		return;

	/* no ps display for stand-alone backend */
	if (!IsUnderPostmaster)
		return;

#ifdef PS_USE_CLOBBER_ARGV
	/* If ps_buffer is a pointer, it might still be null */
	if (!ps_buffer)
		return;
#endif

	/* Update ps_buffer to contain both fixed part and activity */
	strlcpy(ps_buffer + ps_buffer_fixed_size, activity,
			ps_buffer_size - ps_buffer_fixed_size);
	ps_buffer_cur_len = strlen(ps_buffer);

	/* Transmit new setting to kernel, if necessary */

#ifdef PS_USE_SETPROCTITLE
	setproctitle("%s", ps_buffer);
#elif defined(PS_USE_SETPROCTITLE_FAST)
	setproctitle_fast("%s", ps_buffer);
#endif

#ifdef PS_USE_PSTAT
	{
		union pstun pst;

		pst.pst_command = ps_buffer;
		pstat(PSTAT_SETCMD, pst, ps_buffer_cur_len, 0, 0);
	}
#endif							/* PS_USE_PSTAT */

#ifdef PS_USE_PS_STRINGS
	PS_STRINGS->ps_nargvstr = 1;
	PS_STRINGS->ps_argvstr = ps_buffer;
#endif							/* PS_USE_PS_STRINGS */

#ifdef PS_USE_CLOBBER_ARGV
	/* pad unused memory; need only clobber remainder of old status string */
	if (last_status_len > ps_buffer_cur_len)
		MemSet(ps_buffer + ps_buffer_cur_len, PS_PADDING,
			   last_status_len - ps_buffer_cur_len);
	last_status_len = ps_buffer_cur_len;
#endif							/* PS_USE_CLOBBER_ARGV */

#ifdef PS_USE_WIN32
	{
		/*
		 * Win32 does not support showing any changed arguments. To make it at
		 * all possible to track which backend is doing what, we create a
		 * named object that can be viewed with for example Process Explorer.
		 */
		static HANDLE ident_handle = INVALID_HANDLE_VALUE;
		char		name[PS_BUFFER_SIZE + 32];

		if (ident_handle != INVALID_HANDLE_VALUE)
			CloseHandle(ident_handle);

		sprintf(name, "pgident(%d): %s", MyProcPid, ps_buffer);

		ident_handle = CreateEvent(NULL, TRUE, FALSE, name);
	}
#endif							/* PS_USE_WIN32 */
#endif							/* not PS_USE_NONE */
}