#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  b_p_ma; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 TYPE_1__* curbuf ; 
 int /*<<< orphan*/  e_modifiable ; 
 int /*<<< orphan*/  e_sandbox ; 
 int /*<<< orphan*/  e_secure ; 
 scalar_t__ sandbox ; 
 scalar_t__ textlock ; 

int
undo_allowed()
{
    /* Don't allow changes when 'modifiable' is off.  */
    if (!curbuf->b_p_ma)
    {
	EMSG(_(e_modifiable));
	return FALSE;
    }

#ifdef HAVE_SANDBOX
    /* In the sandbox it's not allowed to change the text. */
    if (sandbox != 0)
    {
	EMSG(_(e_sandbox));
	return FALSE;
    }
#endif

    /* Don't allow changes in the buffer while editing the cmdline.  The
     * caller of getcmdline() may get confused. */
    if (textlock != 0)
    {
	EMSG(_(e_secure));
	return FALSE;
    }

    return TRUE;
}