#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hPin; } ;
struct TYPE_8__ {int Numerator; int Denominator; } ;
struct TYPE_9__ {int Size; TYPE_1__ PresentationTime; int /*<<< orphan*/  Data; scalar_t__ DataUsed; scalar_t__ FrameExtent; int /*<<< orphan*/  hEvent; } ;
typedef  TYPE_2__ OVERLAPPED ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER8 ;
typedef  TYPE_3__* LPCDirectSoundBuffer ;
typedef  TYPE_2__ KSSTREAM_HEADER ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDirectSoundBuffer ; 
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,scalar_t__*,TYPE_2__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IOCTL_KS_WRITE_STREAM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lpVtbl ; 

DWORD
PrimaryDirectSoundBuffer_Write(
    LPDIRECTSOUNDBUFFER8 iface,
    LPVOID Buffer,
    DWORD  BufferSize)
{
    KSSTREAM_HEADER Header;
    DWORD Result, BytesTransferred;
    OVERLAPPED Overlapped;

    LPCDirectSoundBuffer This = (LPCDirectSoundBuffer)CONTAINING_RECORD(iface, CDirectSoundBuffer, lpVtbl);

    ZeroMemory(&Overlapped, sizeof(OVERLAPPED));
    Overlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);


    ASSERT(This->hPin);
    ZeroMemory(&Header, sizeof(KSSTREAM_HEADER));

    Header.FrameExtent = BufferSize;
    Header.DataUsed = BufferSize;
    Header.Data = Buffer;
    Header.Size = sizeof(KSSTREAM_HEADER);
    Header.PresentationTime.Numerator = 1;
    Header.PresentationTime.Denominator = 1;

    Result = DeviceIoControl(This->hPin, IOCTL_KS_WRITE_STREAM, NULL, 0, &Header, sizeof(KSSTREAM_HEADER), &BytesTransferred, &Overlapped);

    if (Result != ERROR_SUCCESS)
        return 0;

    return BytesTransferred;
}