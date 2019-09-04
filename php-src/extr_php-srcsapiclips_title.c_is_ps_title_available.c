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
 int PS_TITLE_NOT_INITIALIZED ; 
 int PS_TITLE_SUCCESS ; 
 int /*<<< orphan*/  save_argv ; 

int is_ps_title_available()
{
#ifdef PS_USE_NONE
    return PS_TITLE_NOT_AVAILABLE; /* disabled functionality */
#endif

    if (!save_argv)
        return PS_TITLE_NOT_INITIALIZED;

#ifdef PS_USE_CLOBBER_ARGV
    if (!ps_buffer)
        return PS_TITLE_BUFFER_NOT_AVAILABLE;
#endif /* PS_USE_CLOBBER_ARGV */

    return PS_TITLE_SUCCESS;
}