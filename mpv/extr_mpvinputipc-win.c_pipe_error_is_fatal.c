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
typedef  int DWORD ;

/* Variables and functions */
#define  ERROR_BROKEN_PIPE 131 
#define  ERROR_HANDLE_EOF 130 
#define  ERROR_NO_DATA 129 
#define  ERROR_PIPE_NOT_CONNECTED 128 

__attribute__((used)) static bool pipe_error_is_fatal(DWORD error)
{
    switch (error) {
    case 0:
    case ERROR_HANDLE_EOF:
    case ERROR_BROKEN_PIPE:
    case ERROR_PIPE_NOT_CONNECTED:
    case ERROR_NO_DATA:
        return false;
    }
    return true;
}