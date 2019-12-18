#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int function; int /*<<< orphan*/  parameter; } ;
struct TYPE_6__ {int /*<<< orphan*/ * wave_queue; TYPE_1__ thread; int /*<<< orphan*/  kernel_device_handle; } ;
typedef  TYPE_2__ SessionInfo ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  MMRESULT ;
typedef  int /*<<< orphan*/  LPWAVEHDR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
#define  DRVM_TERMINATE 140 
 int /*<<< orphan*/  GetDeviceData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  IOCTL_WAVE_GET_PITCH ; 
 int /*<<< orphan*/  IOCTL_WAVE_GET_PLAYBACK_RATE ; 
 int /*<<< orphan*/  IOCTL_WAVE_GET_VOLUME ; 
 int /*<<< orphan*/  IOCTL_WAVE_SET_PITCH ; 
 int /*<<< orphan*/  IOCTL_WAVE_SET_PLAYBACK_RATE ; 
 int /*<<< orphan*/  MMSYSERR_ERROR ; 
 int /*<<< orphan*/  MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  QueueWaveBuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDeviceData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WAVERR_STILLPLAYING ; 
#define  WODM_CLOSE 139 
#define  WODM_GETPITCH 138 
#define  WODM_GETPLAYBACKRATE 137 
#define  WODM_GETPOS 136 
#define  WODM_GETVOLUME 135 
#define  WODM_PAUSE 134 
#define  WODM_RESET 133 
#define  WODM_RESTART 132 
#define  WODM_SETPITCH 131 
#define  WODM_SETPLAYBACKRATE 130 
#define  WODM_SETVOLUME 129 
#define  WODM_WRITE 128 

DWORD
ProcessSessionThreadRequest(SessionInfo* session_info)
{
    MMRESULT result = MMSYSERR_NOERROR;

    switch ( session_info->thread.function )
    {
        case WODM_WRITE :
        {
            result = QueueWaveBuffer(session_info,
                                     (LPWAVEHDR) session_info->thread.parameter);
            break;
        }

        case WODM_RESET :
        {
            /* TODO */
            break;
        }

        case WODM_PAUSE :
        {
            /* TODO */
            break;
        }

        case WODM_RESTART :
        {
            /* TODO */
            break;
        }

        case WODM_GETPOS :
        {
            /* TODO */
            break;
        }

        case WODM_SETPITCH :
        {
            result = SetDeviceData(session_info->kernel_device_handle,
                                   IOCTL_WAVE_SET_PITCH,
                                   (PBYTE) session_info->thread.parameter,
                                   sizeof(DWORD));
            break;
        }

        case WODM_GETPITCH :
        {
            result = GetDeviceData(session_info->kernel_device_handle,
                                   IOCTL_WAVE_GET_PITCH,
                                   (PBYTE) session_info->thread.parameter,
                                   sizeof(DWORD));
            break;
        }

        case WODM_SETVOLUME :
        {
            break;
        }

        case WODM_GETVOLUME :
        {
#if 0
            result = GetDeviceData(session_info->kernel_device_handle,
                                   IOCTL_WAVE_GET_VOLUME,
                                   (PBYTE) session_info->thread.parameter,);
#endif
            break;
        }

        case WODM_SETPLAYBACKRATE :
        {
            result = SetDeviceData(session_info->kernel_device_handle,
                                   IOCTL_WAVE_SET_PLAYBACK_RATE,
                                   (PBYTE) session_info->thread.parameter,
                                   sizeof(DWORD));
            break;
        }

        case WODM_GETPLAYBACKRATE :
        {
            result = GetDeviceData(session_info->kernel_device_handle,
                                   IOCTL_WAVE_GET_PLAYBACK_RATE,
                                   (PBYTE) session_info->thread.parameter,
                                   sizeof(DWORD));
            break;
        }

        case WODM_CLOSE :
        {
            DPRINT("Thread was asked if OK to close device\n");

            if ( session_info->wave_queue != NULL )
                result = WAVERR_STILLPLAYING;
            else
                result = MMSYSERR_NOERROR;

            break;
        }

        case DRVM_TERMINATE :
        {
            DPRINT("Terminating thread...\n");
            result = MMSYSERR_NOERROR;
            break;
        }

        default :
        {
            DPRINT("INVALID FUNCTION\n");
            result = MMSYSERR_ERROR;
            break;
        }
    }

    /* We're done with the function now */

    return result;
}