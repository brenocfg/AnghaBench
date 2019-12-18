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
struct TYPE_4__ {scalar_t__ QuadPart; } ;
struct chunk_entry {scalar_t__ id; TYPE_1__ offset; } ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FOURCC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FOURCC_LIST ; 
 scalar_t__ FOURCC_RIFF ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 

__attribute__((used)) static inline HRESULT stream_reset_chunk_data(IStream *stream, const struct chunk_entry *chunk)
{
    LARGE_INTEGER offset;

    offset.QuadPart = chunk->offset.QuadPart + sizeof(FOURCC) + sizeof(DWORD);
    if (chunk->id == FOURCC_RIFF || chunk->id == FOURCC_LIST)
        offset.QuadPart += sizeof(FOURCC);

    return IStream_Seek(stream, offset, STREAM_SEEK_SET, NULL);
}