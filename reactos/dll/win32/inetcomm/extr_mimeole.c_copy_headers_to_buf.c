#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int QuadPart; } ;
typedef  int LONGLONG ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int PARSER_BUF_SIZE ; 
 int /*<<< orphan*/  STREAM_SEEK_CUR ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static HRESULT copy_headers_to_buf(IStream *stm, char **ptr)
{
    char *buf = NULL;
    DWORD size = PARSER_BUF_SIZE, offset = 0, last_end = 0;
    HRESULT hr;
    BOOL done = FALSE;

    *ptr = NULL;

    do
    {
        char *end;
        DWORD read;

        if(!buf)
            buf = HeapAlloc(GetProcessHeap(), 0, size + 1);
        else
        {
            size *= 2;
            buf = HeapReAlloc(GetProcessHeap(), 0, buf, size + 1);
        }
        if(!buf)
        {
            hr = E_OUTOFMEMORY;
            goto fail;
        }

        hr = IStream_Read(stm, buf + offset, size - offset, &read);
        if(FAILED(hr)) goto fail;

        offset += read;
        buf[offset] = '\0';

        if(read == 0) done = TRUE;

        while(!done && (end = strstr(buf + last_end, "\r\n")))
        {
            DWORD new_end = end - buf + 2;
            if(new_end - last_end == 2)
            {
                LARGE_INTEGER off;
                off.QuadPart = (LONGLONG)new_end - offset;
                IStream_Seek(stm, off, STREAM_SEEK_CUR, NULL);
                buf[new_end] = '\0';
                done = TRUE;
            }
            else
                last_end = new_end;
        }
    } while(!done);

    *ptr = buf;
    return S_OK;

fail:
    HeapFree(GetProcessHeap(), 0, buf);
    return hr;
}