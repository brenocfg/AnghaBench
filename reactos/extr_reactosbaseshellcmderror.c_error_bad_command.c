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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ConErrResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_ERROR_BADCOMMAND ; 
 int nErrorLevel ; 

VOID error_bad_command (LPTSTR s)
{
    ConErrResPrintf(STRING_ERROR_BADCOMMAND, s);
    nErrorLevel = 9009;
}