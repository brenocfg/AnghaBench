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
typedef  int char_u ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * breakat_flags ; 
 int* p_breakat ; 

__attribute__((used)) static void
fill_breakat_flags()
{
    char_u	*p;
    int		i;

    for (i = 0; i < 256; i++)
	breakat_flags[i] = FALSE;

    if (p_breakat != NULL)
	for (p = p_breakat; *p; p++)
	    breakat_flags[*p] = TRUE;
}