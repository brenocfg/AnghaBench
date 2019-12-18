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
typedef  int ULONG ;
struct TYPE_5__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_6__ {int QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,int*,int,int*) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (int*,char*,int) ; 

__attribute__((used)) static BOOL has_png_transparency_chunk(IStream *pIStream)
{
    LARGE_INTEGER seek;
    BOOL has_tRNS = FALSE;
    HRESULT hr;
    BYTE header[8];

    seek.QuadPart = 8;
    do
    {
        ULARGE_INTEGER chunk_start;
        ULONG bytesread, chunk_size;

        hr = IStream_Seek(pIStream, seek, STREAM_SEEK_SET, &chunk_start);
        if (FAILED(hr)) break;

        hr = IStream_Read(pIStream, header, 8, &bytesread);
        if (FAILED(hr) || bytesread < 8) break;

        chunk_size = (header[0] << 24) | (header[1] << 16) | (header[2] << 8) | header[3];
        if (!memcmp(&header[4], "tRNS", 4))
        {
            has_tRNS = TRUE;
            break;
        }

        seek.QuadPart = chunk_start.QuadPart + chunk_size + 12; /* skip data and CRC */
    } while (memcmp(&header[4], "IDAT", 4) && memcmp(&header[4], "IEND", 4));

    TRACE("has_tRNS = %d\n", has_tRNS);
    return has_tRNS;
}