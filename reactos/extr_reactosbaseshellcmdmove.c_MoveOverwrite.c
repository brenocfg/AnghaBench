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
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConOutResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FilePromptYNA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_MOVE_HELP1 ; 

__attribute__((used)) static INT MoveOverwrite (LPTSTR fn)
{
    /* ask the user if they want to override */
    INT res;
    ConOutResPrintf(STRING_MOVE_HELP1, fn);
    res = FilePromptYNA (0);
    return res;
}