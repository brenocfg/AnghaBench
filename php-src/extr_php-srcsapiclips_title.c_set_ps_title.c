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

/* Variables and functions */
 int PS_TITLE_SUCCESS ; 
 int is_ps_title_available () ; 
 char* ps_buffer ; 
 int /*<<< orphan*/  ps_buffer_cur_len ; 
 int ps_buffer_size ; 
 int /*<<< orphan*/  strlen (char*) ; 
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