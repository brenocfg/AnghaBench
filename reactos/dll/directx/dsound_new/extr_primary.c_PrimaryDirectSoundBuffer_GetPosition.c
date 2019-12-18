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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ WriteOffset; scalar_t__ PlayOffset; } ;
struct TYPE_5__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Set; int /*<<< orphan*/  Id; } ;
struct TYPE_4__ {int /*<<< orphan*/  hPin; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__* LPDWORD ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER8 ;
typedef  TYPE_1__* LPCDirectSoundBuffer ;
typedef  TYPE_2__ KSPROPERTY ;
typedef  TYPE_3__ KSAUDIO_POSITION ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CDirectSoundBuffer ; 
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DSERR_UNSUPPORTED ; 
 int /*<<< orphan*/  DS_OK ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  IOCTL_KS_PROPERTY ; 
 int /*<<< orphan*/  KSPROPERTY_AUDIO_POSITION ; 
 int /*<<< orphan*/  KSPROPERTY_TYPE_GET ; 
 int /*<<< orphan*/  KSPROPSETID_Audio ; 
 scalar_t__ SyncOverlappedDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpVtbl ; 

HRESULT
PrimaryDirectSoundBuffer_GetPosition(
    LPDIRECTSOUNDBUFFER8 iface,
    LPDWORD pdwCurrentPlayCursor,
    LPDWORD pdwCurrentWriteCursor)
{
    KSAUDIO_POSITION Position;
    KSPROPERTY Request;
    DWORD Result;
    LPCDirectSoundBuffer This = (LPCDirectSoundBuffer)CONTAINING_RECORD(iface, CDirectSoundBuffer, lpVtbl);

    //DPRINT("PrimaryDirectSoundBuffer_GetPosition\n");

    if (!This->hPin)
    {
        if (pdwCurrentPlayCursor)
            *pdwCurrentPlayCursor = 0;

        if (pdwCurrentWriteCursor)
            *pdwCurrentWriteCursor = 0;

        DPRINT("No Audio Pin\n");
        return DS_OK;
    }

    /* setup audio position property request */
    Request.Id = KSPROPERTY_AUDIO_POSITION;
    Request.Set = KSPROPSETID_Audio;
    Request.Flags = KSPROPERTY_TYPE_GET;


    Result = SyncOverlappedDeviceIoControl(This->hPin, IOCTL_KS_PROPERTY, (PVOID)&Request, sizeof(KSPROPERTY), (PVOID)&Position, sizeof(KSAUDIO_POSITION), NULL);

    if (Result != ERROR_SUCCESS)
    {
        DPRINT("GetPosition failed with %x\n", Result);
        return DSERR_UNSUPPORTED;
    }

    //DPRINT("Play %I64u Write %I64u \n", Position.PlayOffset, Position.WriteOffset);

    if (pdwCurrentPlayCursor)
        *pdwCurrentPlayCursor = (DWORD)Position.PlayOffset;

    if (pdwCurrentWriteCursor)
        *pdwCurrentWriteCursor = (DWORD)Position.WriteOffset;

    return DS_OK;
}