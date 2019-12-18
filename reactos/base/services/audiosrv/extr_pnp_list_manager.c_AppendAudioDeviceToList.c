#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; scalar_t__ max_size; int /*<<< orphan*/  device_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ PnP_AudioDevice ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LockAudioDeviceList () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnlockAudioDeviceList () ; 
 scalar_t__ WideStringSize (int /*<<< orphan*/ ) ; 
 TYPE_3__* audio_device_list ; 
 int /*<<< orphan*/  logmsg (char*) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_1__*,int) ; 

BOOL
AppendAudioDeviceToList(PnP_AudioDevice* device)
{
    int device_info_size;

    /* Figure out the actual structure size */
    device_info_size = sizeof(PnP_AudioDevice);
    device_info_size += WideStringSize(device->path);

    LockAudioDeviceList();

/*
    printf("list size is %d\n", audio_device_list->size);
    printf("device info size is %d bytes\n", device_info_size);
*/

    /* We DON'T want to overshoot the end of the buffer! */
    if (audio_device_list->size + device_info_size > audio_device_list->max_size)
    {
        /*printf("max_size would be exceeded! Failing...\n");*/
        
        UnlockAudioDeviceList();
        
        return FALSE;
    }

    /* Commit the device descriptor to the list */
    memcpy((char*)audio_device_list + audio_device_list->size,
           device,
           device_info_size);

    /* Update the header */
    audio_device_list->device_count ++;
    audio_device_list->size += device_info_size;

    UnlockAudioDeviceList();

    logmsg("Device added to list\n");

    return TRUE;
}