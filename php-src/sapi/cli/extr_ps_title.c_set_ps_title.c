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
typedef  int /*<<< orphan*/  wchar_t ;
union pstun {char* pst_command; } ;
struct TYPE_2__ {int ps_nargvstr; char* ps_argvstr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSTAT_SETCMD ; 
 int /*<<< orphan*/  PS_PADDING ; 
 TYPE_1__* PS_STRINGS ; 
 int PS_TITLE_SUCCESS ; 
 int PS_TITLE_WINDOWS_ERROR ; 
 int /*<<< orphan*/  SetConsoleTitleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int is_ps_title_available () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * php_win32_cp_any_to_w (char*) ; 
 char* ps_buffer ; 
 int ps_buffer_cur_len ; 
 int ps_buffer_size ; 
 int /*<<< orphan*/  pstat (int /*<<< orphan*/ ,union pstun,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setproctitle (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int set_ps_title(const char* title)
{
    int rc = is_ps_title_available();
    if (rc != PS_TITLE_SUCCESS)
        return rc;

    strncpy(ps_buffer, title, ps_buffer_size);
    ps_buffer[ps_buffer_size - 1] = '\0';
    ps_buffer_cur_len = strlen(ps_buffer);

#ifdef PS_USE_SETPROCTITLE
    setproctitle("%s", ps_buffer);
#endif

#ifdef PS_USE_PSTAT
    {
        union pstun pst;

        pst.pst_command = ps_buffer;
        pstat(PSTAT_SETCMD, pst, ps_buffer_cur_len, 0, 0);
    }
#endif /* PS_USE_PSTAT */

#ifdef PS_USE_PS_STRINGS
    PS_STRINGS->ps_nargvstr = 1;
    PS_STRINGS->ps_argvstr = ps_buffer;
#endif /* PS_USE_PS_STRINGS */

#ifdef PS_USE_CLOBBER_ARGV
    /* pad unused memory */
    if (ps_buffer_cur_len < ps_buffer_size)
    {
        memset(ps_buffer + ps_buffer_cur_len, PS_PADDING,
               ps_buffer_size - ps_buffer_cur_len);
    }
#endif /* PS_USE_CLOBBER_ARGV */

#ifdef PS_USE_WIN32
    {
	wchar_t *ps_buffer_w = php_win32_cp_any_to_w(ps_buffer);

        if (!ps_buffer_w || !SetConsoleTitleW(ps_buffer_w)) {
            return PS_TITLE_WINDOWS_ERROR;
	}

	free(ps_buffer_w);
    }
#endif /* PS_USE_WIN32 */

    return PS_TITLE_SUCCESS;
}