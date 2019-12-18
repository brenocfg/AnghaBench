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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_ECHO_INPUT ; 
 int /*<<< orphan*/  ENABLE_LINE_INPUT ; 
 int /*<<< orphan*/  ENABLE_PROCESSED_INPUT ; 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assure_stdin_handle () ; 
 int /*<<< orphan*/  orig_mode ; 
 int /*<<< orphan*/  std_in ; 

void mp_hal_stdio_mode_raw(void) {
    assure_stdin_handle();
    GetConsoleMode(std_in, &orig_mode);
    DWORD mode = orig_mode;
    mode &= ~ENABLE_ECHO_INPUT;
    mode &= ~ENABLE_LINE_INPUT;
    mode &= ~ENABLE_PROCESSED_INPUT;
    SetConsoleMode(std_in, mode);
}