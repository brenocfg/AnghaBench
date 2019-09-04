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

/* Variables and functions */
#define  NC_BADFILE 132 
#define  NC_NOMEM 131 
#define  NC_NONETCONFIG 130 
#define  NC_NOTFOUND 129 
#define  NC_NOTINIT 128 
 char** _nc_errors ; 
 int nc_error ; 

char *
nc_sperror()
{
    const char *message;

    switch(nc_error) {
    case NC_NONETCONFIG:
		message = _nc_errors[0];
		break;
    case NC_NOMEM:
		message = _nc_errors[1];
		break;
    case NC_NOTINIT:
		message = _nc_errors[2];
		break;
    case NC_BADFILE:
		message = _nc_errors[3];
		break;
    case NC_NOTFOUND:
		message = _nc_errors[4];
		break;
    default:
		message = "Unknown network selection error";
    }
    /* LINTED const castaway */
    return ((char *)message);
}