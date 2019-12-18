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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static HRESULT read_from_stream(IStream *stream, void *data, ULONG size)
{
    ULONG bytes_read;
    HRESULT hr;

    hr = IStream_Read(stream, data, size, &bytes_read);
    if(FAILED(hr)){
        TRACE("IStream_Read failed: %08x\n", hr);
        return hr;
    }
    if (bytes_read < size) {
        TRACE("Didn't read full chunk: %u < %u\n", bytes_read, size);
        return E_FAIL;
    }

    return S_OK;
}