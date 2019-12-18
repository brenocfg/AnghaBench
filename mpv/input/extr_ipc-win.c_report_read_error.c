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
struct client_arg {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (struct client_arg*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct client_arg*,char*) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ pipe_error_is_fatal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_read_error(struct client_arg *arg, DWORD error)
{
    // Only report the error if it's not just due to the pipe closing
    if (pipe_error_is_fatal(error)) {
        MP_ERR(arg, "Error reading from pipe: %s\n",
            mp_HRESULT_to_str(HRESULT_FROM_WIN32(error)));
    } else {
        MP_VERBOSE(arg, "Client disconnected\n");
    }
}