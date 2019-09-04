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
 scalar_t__ ps_buffer_cur_len ; 

int get_ps_title(int *displen, const char** string)
{
    int rc = is_ps_title_available();
    if (rc != PS_TITLE_SUCCESS)
        return rc;

#ifdef PS_USE_WIN32
    {
	wchar_t ps_buffer_w[MAX_PATH];
	char *tmp;

        if (!(ps_buffer_cur_len = GetConsoleTitleW(ps_buffer_w, (DWORD)sizeof(ps_buffer_w)))) {
            return PS_TITLE_WINDOWS_ERROR;
	}

	tmp = php_win32_cp_conv_w_to_any(ps_buffer_w, PHP_WIN32_CP_IGNORE_LEN, &ps_buffer_cur_len);
	if (!tmp) {
            return PS_TITLE_WINDOWS_ERROR;
	}

	ps_buffer_cur_len = ps_buffer_cur_len > sizeof(ps_buffer)-1 ? sizeof(ps_buffer)-1 : ps_buffer_cur_len;

	memmove(ps_buffer, tmp, ps_buffer_cur_len);
	free(tmp);
    }
#endif
    *displen = (int)ps_buffer_cur_len;
    *string = ps_buffer;
    return PS_TITLE_SUCCESS;
}