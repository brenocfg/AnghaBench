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
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  int /*<<< orphan*/  INPUT_RECORD ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  read_console_input (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
peek_console_input(
    HANDLE	    hInput,
    INPUT_RECORD    *lpBuffer,
    DWORD	    nLength,
    LPDWORD	    lpEvents)
{
    return read_console_input(hInput, lpBuffer, -1, lpEvents);
}