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
typedef  scalar_t__ char_u ;

/* Variables and functions */
 scalar_t__ ESC ; 
 scalar_t__ NUL ; 
 scalar_t__ STRLEN (scalar_t__*) ; 
 int /*<<< orphan*/ * last_insert ; 
 int last_insert_skip ; 
 scalar_t__* vim_strsave (int /*<<< orphan*/ *) ; 

char_u *
get_last_insert_save()
{
    char_u	*s;
    int		len;

    if (last_insert == NULL)
	return NULL;
    s = vim_strsave(last_insert + last_insert_skip);
    if (s != NULL)
    {
	len = (int)STRLEN(s);
	if (len > 0 && s[len - 1] == ESC)	/* remove trailing ESC */
	    s[len - 1] = NUL;
    }
    return s;
}