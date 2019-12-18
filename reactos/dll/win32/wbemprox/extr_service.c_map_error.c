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
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
#define  ERROR_ACCESS_DENIED 135 
#define  ERROR_DEPENDENT_SERVICES_RUNNING 134 
#define  ERROR_INVALID_SERVICE_CONTROL 133 
#define  ERROR_SERVICE_ALREADY_RUNNING 132 
#define  ERROR_SERVICE_CANNOT_ACCEPT_CTRL 131 
#define  ERROR_SERVICE_NOT_ACTIVE 130 
#define  ERROR_SERVICE_REQUEST_TIMEOUT 129 
#define  ERROR_SUCCESS 128 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static UINT map_error( DWORD error )
{
    switch (error)
    {
    case ERROR_SUCCESS:       return 0;
    case ERROR_ACCESS_DENIED: return 2;
    case ERROR_DEPENDENT_SERVICES_RUNNING: return 3;
    case ERROR_INVALID_SERVICE_CONTROL:    return 4;
    case ERROR_SERVICE_CANNOT_ACCEPT_CTRL: return 5;
    case ERROR_SERVICE_NOT_ACTIVE:         return 6;
    case ERROR_SERVICE_REQUEST_TIMEOUT:    return 7;
    case ERROR_SERVICE_ALREADY_RUNNING:    return 10;
    default:
        WARN("unknown error %u\n", error);
        break;
    }
    return 8;
}