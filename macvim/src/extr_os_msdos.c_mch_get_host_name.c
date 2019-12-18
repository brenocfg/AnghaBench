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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  vim_strncpy (int /*<<< orphan*/ *,char*,int) ; 

void
mch_get_host_name(
    char_u	*s,
    int		len)
{
#ifdef DJGPP
    vim_strncpy(s, "PC (32 bits Vim)", len - 1);
#else
    vim_strncpy(s, "PC (16 bits Vim)", len - 1);
#endif
}