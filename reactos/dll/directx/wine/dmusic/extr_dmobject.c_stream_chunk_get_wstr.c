#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct chunk_entry {scalar_t__ size; } ;
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,scalar_t__*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 size_t min (scalar_t__,scalar_t__) ; 

HRESULT stream_chunk_get_wstr(IStream *stream, const struct chunk_entry *chunk, WCHAR *str,
        ULONG size)
{
    ULONG len;
    HRESULT hr;

    hr = IStream_Read(stream, str, min(chunk->size, size), &len);
    if (FAILED(hr))
        return hr;

    /* Don't assume the string is properly zero terminated */
    str[min(len, size - 1)] = 0;

    if (len < chunk->size)
        return S_FALSE;
    return S_OK;
}