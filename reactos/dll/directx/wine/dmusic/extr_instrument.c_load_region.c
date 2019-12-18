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
struct TYPE_6__ {int fccID; int dwSize; } ;
struct TYPE_5__ {int loop_present; TYPE_2__ wave_link; TYPE_2__ wave_loop; TYPE_2__ wave_sample; TYPE_2__ header; } ;
typedef  TYPE_1__ instrument_region ;
typedef  int /*<<< orphan*/  chunk ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IDirectMusicInstrumentImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DMUS_PRIVATE_CHUNK ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
#define  FOURCC_RGNH 130 
#define  FOURCC_WLNK 129 
#define  FOURCC_WSMP 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  advance_stream (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugstr_fourcc (int) ; 
 int /*<<< orphan*/  read_from_stream (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ subtract_bytes (scalar_t__,int) ; 

__attribute__((used)) static HRESULT load_region(IDirectMusicInstrumentImpl *This, IStream *stream, instrument_region *region, ULONG length)
{
    HRESULT ret;
    DMUS_PRIVATE_CHUNK chunk;

    TRACE("(%p, %p, %p, %u)\n", This, stream, region, length);

    while (length)
    {
        ret = read_from_stream(stream, &chunk, sizeof(chunk));
        if (FAILED(ret))
            return ret;

        length = subtract_bytes(length, sizeof(chunk));

        switch (chunk.fccID)
        {
            case FOURCC_RGNH:
                TRACE("RGNH chunk (region header): %u bytes\n", chunk.dwSize);

                ret = read_from_stream(stream, &region->header, sizeof(region->header));
                if (FAILED(ret))
                    return ret;

                length = subtract_bytes(length, sizeof(region->header));
                break;

            case FOURCC_WSMP:
                TRACE("WSMP chunk (wave sample): %u bytes\n", chunk.dwSize);

                ret = read_from_stream(stream, &region->wave_sample, sizeof(region->wave_sample));
                if (FAILED(ret))
                    return ret;
                length = subtract_bytes(length, sizeof(region->wave_sample));

                if (!(region->loop_present = (chunk.dwSize != sizeof(region->wave_sample))))
                    break;

                ret = read_from_stream(stream, &region->wave_loop, sizeof(region->wave_loop));
                if (FAILED(ret))
                    return ret;

                length = subtract_bytes(length, sizeof(region->wave_loop));
                break;

            case FOURCC_WLNK:
                TRACE("WLNK chunk (wave link): %u bytes\n", chunk.dwSize);

                ret = read_from_stream(stream, &region->wave_link, sizeof(region->wave_link));
                if (FAILED(ret))
                    return ret;

                length = subtract_bytes(length, sizeof(region->wave_link));
                break;

            default:
                TRACE("Unknown chunk %s (skipping): %u bytes\n", debugstr_fourcc(chunk.fccID), chunk.dwSize);

                ret = advance_stream(stream, chunk.dwSize);
                if (FAILED(ret))
                    return ret;

                length = subtract_bytes(length, chunk.dwSize);
                break;
        }
    }

    return S_OK;
}