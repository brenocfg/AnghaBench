#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ QuadPart; } ;
struct TYPE_7__ {scalar_t__ QuadPart; } ;
struct TYPE_6__ {TYPE_4__ cbSize; } ;
typedef  TYPE_1__ STATSTG ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_SetSize (int /*<<< orphan*/ *,TYPE_4__) ; 
 int /*<<< orphan*/  IStream_Stat (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  STATFLAG_NONAME ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,scalar_t__) ; 

__attribute__((used)) static HRESULT write_stream( IStream *dst, IStream *src )
{
    HRESULT hr;
    char buf[4096];
    STATSTG stat;
    LARGE_INTEGER pos;
    UINT count, size;

    hr = IStream_Stat( src, &stat, STATFLAG_NONAME );
    if (FAILED( hr )) return hr;

    hr = IStream_SetSize( dst, stat.cbSize );
    if (FAILED( hr )) return hr;

    pos.QuadPart = 0;
    hr = IStream_Seek( dst, pos, STREAM_SEEK_SET, NULL );
    if (FAILED( hr )) return hr;

    for (;;)
    {
        size = min( sizeof(buf), stat.cbSize.QuadPart );
        hr = IStream_Read( src, buf, size, &count );
        if (FAILED( hr ) || count != size)
        {
            WARN("failed to read stream: %08x\n", hr);
            return E_INVALIDARG;
        }
        stat.cbSize.QuadPart -= count;
        if (count)
        {
            size = count;
            hr = IStream_Write( dst, buf, size, &count );
            if (FAILED( hr ) || count != size)
            {
                WARN("failed to write stream: %08x\n", hr);
                return E_INVALIDARG;
            }
        }
        if (!stat.cbSize.QuadPart) break;
    }

    return S_OK;
}