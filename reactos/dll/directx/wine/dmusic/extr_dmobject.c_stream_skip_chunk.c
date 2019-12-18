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
struct TYPE_4__ {int QuadPart; } ;
struct chunk_entry {int size; TYPE_1__ offset; } ;
typedef  int ULONGLONG ;
struct TYPE_5__ {int QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int CHUNK_HDR_SIZE ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 

HRESULT stream_skip_chunk(IStream *stream, struct chunk_entry *chunk)
{
    LARGE_INTEGER end;

    end.QuadPart = (chunk->offset.QuadPart + CHUNK_HDR_SIZE + chunk->size + 1) & ~(ULONGLONG)1;

    return IStream_Seek(stream, end, STREAM_SEEK_SET, NULL);
}