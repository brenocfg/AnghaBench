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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KillAudioDeviceListLock () ; 
 int /*<<< orphan*/  LockAudioDeviceList () ; 
 int /*<<< orphan*/  UnlockAudioDeviceList () ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * audio_device_list ; 
 int /*<<< orphan*/ * device_list_file ; 
 int /*<<< orphan*/  logmsg (char*) ; 

VOID
DestroyAudioDeviceList()
{
    logmsg("Destroying device list\n");

    LockAudioDeviceList();

    /*printf("Unmapping view\n");*/
    UnmapViewOfFile(audio_device_list);
    audio_device_list = NULL;

    /*printf("Closing memory mapped file\n");*/
    CloseHandle(device_list_file);
    device_list_file = NULL;

    UnlockAudioDeviceList();

    /*printf("Killing devlist lock\n");*/
    KillAudioDeviceListLock();
}