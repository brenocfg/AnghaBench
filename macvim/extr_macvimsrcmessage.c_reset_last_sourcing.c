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
 scalar_t__ last_sourcing_lnum ; 
 int /*<<< orphan*/ * last_sourcing_name ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

void
reset_last_sourcing()
{
    vim_free(last_sourcing_name);
    last_sourcing_name = NULL;
    last_sourcing_lnum = 0;
}