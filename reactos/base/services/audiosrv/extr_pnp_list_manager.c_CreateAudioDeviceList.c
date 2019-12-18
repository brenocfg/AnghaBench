#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; scalar_t__ device_count; int /*<<< orphan*/  max_size; } ;
typedef  int /*<<< orphan*/  PnP_AudioHeader ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_LIST_NAME ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMappingW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_MAP_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  InitializeAudioDeviceListLock () ; 
 int /*<<< orphan*/  KillAudioDeviceListLock () ; 
 int /*<<< orphan*/  LockAudioDeviceList () ; 
 TYPE_1__* MapViewOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnlockAudioDeviceList () ; 
 TYPE_1__* audio_device_list ; 
 int /*<<< orphan*/ * device_list_file ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
CreateAudioDeviceList(DWORD max_size)
{
/*    printf("Initializing memory device list lock\n");*/

    if (!InitializeAudioDeviceListLock())
    {
        /*printf("Failed!\n");*/
        return FALSE;
    }

    /* Preliminary locking - the list memory will likely be a big
       buffer of gibberish at this point so we don't want anyone
       turning up before we're ready... */
    LockAudioDeviceList();

    logmsg("Creating file mapping\n");
    /* Expose our device list to the world */
    device_list_file = CreateFileMappingW(INVALID_HANDLE_VALUE,
                                          NULL,
                                          PAGE_READWRITE,
                                          0,
                                          max_size,
                                          AUDIO_LIST_NAME);
    if (!device_list_file)
    {
        logmsg("Creation of audio device list failed (err %d)\n", GetLastError());

        UnlockAudioDeviceList();
        KillAudioDeviceListLock();

        return FALSE;
    }

    logmsg("Mapping view of file\n");
    /* Of course, we'll need to access the list ourselves */
    audio_device_list = MapViewOfFile(device_list_file,
                                      FILE_MAP_WRITE,
                                      0,
                                      0,
                                      max_size);
    if (!audio_device_list)
    {
        logmsg("MapViewOfFile FAILED (err %d)\n", GetLastError());

        CloseHandle(device_list_file);
        device_list_file = NULL;

        UnlockAudioDeviceList();
        KillAudioDeviceListLock();

        return FALSE;
    }

    /* Clear the mem to avoid any random stray data */
    memset(audio_device_list, 0, max_size);

    /* Don't want devices to overwrite the list! */
    audio_device_list->size = sizeof(PnP_AudioHeader);
    audio_device_list->max_size = max_size;
    audio_device_list->device_count = 0;

    UnlockAudioDeviceList();

    logmsg("Device list created\n");

    return TRUE;
}