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
 scalar_t__ STRCMP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * use_viminfo ; 

__attribute__((used)) static int
no_viminfo()
{
    /* "vim -i NONE" does not read or write a viminfo file */
    return (use_viminfo != NULL && STRCMP(use_viminfo, "NONE") == 0);
}