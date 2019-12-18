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
typedef  int /*<<< orphan*/  MMRESULT ;

/* Variables and functions */
#define  ERROR_ACCESS_DENIED 135 
#define  ERROR_BUSY 134 
#define  ERROR_INSUFFICIENT_BUFFER 133 
#define  ERROR_INVALID_FUNCTION 132 
#define  ERROR_IO_PENDING 131 
#define  ERROR_NOT_ENOUGH_MEMORY 130 
#define  ERROR_NOT_SUPPORTED 129 
 int /*<<< orphan*/  MMSYSERR_ALLOCATED ; 
 int /*<<< orphan*/  MMSYSERR_BADDEVICEID ; 
 int /*<<< orphan*/  MMSYSERR_ERROR ; 
 int /*<<< orphan*/  MMSYSERR_INVALPARAM ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOMEM ; 
 int /*<<< orphan*/  MMSYSERR_NOTSUPPORTED ; 
#define  NO_ERROR 128 

MMRESULT
ErrorToMmResult(UINT error_code)
{
    switch ( error_code )
    {
        case NO_ERROR :
        case ERROR_IO_PENDING :
            return MMSYSERR_NOERROR;

        case ERROR_BUSY :
            return MMSYSERR_ALLOCATED;

        case ERROR_NOT_SUPPORTED :
        case ERROR_INVALID_FUNCTION :
            return MMSYSERR_NOTSUPPORTED;

        case ERROR_NOT_ENOUGH_MEMORY :
            return MMSYSERR_NOMEM;

        case ERROR_ACCESS_DENIED :
            return MMSYSERR_BADDEVICEID;

        case ERROR_INSUFFICIENT_BUFFER :
            return MMSYSERR_INVALPARAM;
    };

    /* If all else fails, it's just a plain old error */

    return MMSYSERR_ERROR;
}