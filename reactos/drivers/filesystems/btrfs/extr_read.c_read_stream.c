#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_5__ {TYPE_1__ adsdata; } ;
typedef  TYPE_2__ fcb ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_END_OF_FILE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 

NTSTATUS read_stream(fcb* fcb, uint8_t* data, uint64_t start, ULONG length, ULONG* pbr) {
    ULONG readlen;

    TRACE("(%p, %p, %I64x, %I64x, %p)\n", fcb, data, start, length, pbr);

    if (pbr) *pbr = 0;

    if (start >= fcb->adsdata.Length) {
        TRACE("tried to read beyond end of stream\n");
        return STATUS_END_OF_FILE;
    }

    if (length == 0) {
        WARN("tried to read zero bytes\n");
        return STATUS_SUCCESS;
    }

    if (start + length < fcb->adsdata.Length)
        readlen = length;
    else
        readlen = fcb->adsdata.Length - (ULONG)start;

    if (readlen > 0)
        RtlCopyMemory(data + start, fcb->adsdata.Buffer, readlen);

    if (pbr) *pbr = readlen;

    return STATUS_SUCCESS;
}