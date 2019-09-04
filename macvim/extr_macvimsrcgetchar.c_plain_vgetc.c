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
 int K_HOR_SCROLLBAR ; 
 int K_IGNORE ; 
 int K_VER_SCROLLBAR ; 
 int safe_vgetc () ; 

int
plain_vgetc()
{
    int c;

    do
    {
	c = safe_vgetc();
    } while (c == K_IGNORE || c == K_VER_SCROLLBAR || c == K_HOR_SCROLLBAR);
    return c;
}