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
 int /*<<< orphan*/  STRCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_showcmd () ; 
 int /*<<< orphan*/  old_showcmd_buf ; 
 int /*<<< orphan*/  p_sc ; 
 int /*<<< orphan*/  showcmd_buf ; 

void
pop_showcmd()
{
    if (!p_sc)
	return;

    STRCPY(showcmd_buf, old_showcmd_buf);

    display_showcmd();
}