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
typedef  int /*<<< orphan*/  LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_REPLACE_ERROR1 ; 
 int /*<<< orphan*/  STRING_REPLACE_HELP3 ; 
 int /*<<< orphan*/  TRUE ; 

void invalid_switch(LPTSTR is)
{
    ConOutResPrintf(STRING_REPLACE_ERROR1,is);
    ConOutResPaging(TRUE,STRING_REPLACE_HELP3);
}