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
typedef  int /*<<< orphan*/  lpos_T ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int NSUBEXP ; 
 scalar_t__ REG_MULTI ; 
 scalar_t__ need_clear_subexpr ; 
 int /*<<< orphan*/  reg_endp ; 
 int /*<<< orphan*/  reg_endpos ; 
 int /*<<< orphan*/  reg_startp ; 
 int /*<<< orphan*/  reg_startpos ; 
 int /*<<< orphan*/  vim_memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
cleanup_subexpr()
{
    if (need_clear_subexpr)
    {
	if (REG_MULTI)
	{
	    /* Use 0xff to set lnum to -1 */
	    vim_memset(reg_startpos, 0xff, sizeof(lpos_T) * NSUBEXP);
	    vim_memset(reg_endpos, 0xff, sizeof(lpos_T) * NSUBEXP);
	}
	else
	{
	    vim_memset(reg_startp, 0, sizeof(char_u *) * NSUBEXP);
	    vim_memset(reg_endp, 0, sizeof(char_u *) * NSUBEXP);
	}
	need_clear_subexpr = FALSE;
    }
}