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
struct TYPE_5__ {int segment; int offset; } ;
struct TYPE_6__ {scalar_t__ BufferSize; TYPE_1__ Buffer; } ;
typedef  TYPE_2__ t_PXENV_TFTP_READ ;
typedef  int /*<<< orphan*/  readData ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG_PTR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  ARC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CallPxe (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESUCCESS ; 
 scalar_t__ NO_FILE ; 
 int /*<<< orphan*/  PXENV_TFTP_READ ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _CachedFile ; 
 scalar_t__ _CachedLength ; 
 scalar_t__ _FilePosition ; 
 scalar_t__ _OpenFile ; 
 scalar_t__ _Packet ; 
 scalar_t__ _PacketPosition ; 

__attribute__((used)) static ARC_STATUS PxeRead(ULONG FileId, VOID* Buffer, ULONG N, ULONG* Count)
{
    t_PXENV_TFTP_READ readData;
    ULONG i;

    *Count = 0;

    if (_OpenFile == NO_FILE || FileId != _OpenFile)
        return EBADF;

    RtlZeroMemory(&readData, sizeof(readData));
    readData.Buffer.segment = ((ULONG_PTR)_Packet & 0xf0000) / 16;
    readData.Buffer.offset = (ULONG_PTR)_Packet & 0xffff;

    // Get new packets as required
    while (N > 0)
    {
        if (N < _CachedLength - _FilePosition)
            i = N;
        else
            i = _CachedLength - _FilePosition;
        if (_CachedFile)
            RtlCopyMemory(Buffer, _CachedFile + _FilePosition, i);
        else
            RtlCopyMemory(Buffer, _Packet + _FilePosition - _PacketPosition, i);
        _FilePosition += i;
        Buffer = (UCHAR*)Buffer + i;
        *Count += i;
        N -= i;
        if (N == 0)
            break;

        if (!CallPxe(PXENV_TFTP_READ, &readData))
            return EIO;
        if (_CachedFile)
            RtlCopyMemory(_CachedFile + _CachedLength, _Packet, readData.BufferSize);
        _PacketPosition = _CachedLength;
        _CachedLength += readData.BufferSize;
    }

    return ESUCCESS;
}