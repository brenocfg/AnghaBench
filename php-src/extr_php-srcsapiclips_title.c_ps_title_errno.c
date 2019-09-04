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
#define  PS_TITLE_BUFFER_NOT_AVAILABLE 131 
#define  PS_TITLE_NOT_AVAILABLE 130 
#define  PS_TITLE_NOT_INITIALIZED 129 
#define  PS_TITLE_SUCCESS 128 

const char* ps_title_errno(int rc)
{
    switch(rc)
    {
    case PS_TITLE_SUCCESS:
        return "Success";

    case PS_TITLE_NOT_AVAILABLE:
        return "Not available on this OS";

    case PS_TITLE_NOT_INITIALIZED:
        return "Not initialized correctly";

    case PS_TITLE_BUFFER_NOT_AVAILABLE:
        return "Buffer not contiguous";

#ifdef PS_USE_WIN32
    case PS_TITLE_WINDOWS_ERROR:
        sprintf(windows_error_details, "Windows error code: %lu", GetLastError());
        return windows_error_details;
#endif
    }

    return "Unknown error code";
}