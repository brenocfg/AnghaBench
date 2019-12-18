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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redir_fd ; 
 scalar_t__ redir_reg ; 
 scalar_t__ redir_vname ; 
 int /*<<< orphan*/  var_redir_stop () ; 

__attribute__((used)) static void
close_redir()
{
    if (redir_fd != NULL)
    {
	fclose(redir_fd);
	redir_fd = NULL;
    }
#ifdef FEAT_EVAL
    redir_reg = 0;
    if (redir_vname)
    {
	var_redir_stop();
	redir_vname = 0;
    }
#endif
}