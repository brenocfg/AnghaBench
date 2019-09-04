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
struct dxbc {int dummy; } ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ TAG_DXBC ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 
 int /*<<< orphan*/  dxbc_add_section (struct dxbc*,scalar_t__,char const*,scalar_t__) ; 
 int /*<<< orphan*/  dxbc_init (struct dxbc*,scalar_t__) ; 
 int /*<<< orphan*/  read_dword (char const**,scalar_t__*) ; 
 int /*<<< orphan*/  skip_dword_unknown (char const**,int) ; 

HRESULT dxbc_parse(const char *data, SIZE_T data_size, struct dxbc *dxbc)
{
    const char *ptr = data;
    HRESULT hr;
    unsigned int i;
    DWORD tag, total_size, chunk_count;

    if (!data)
    {
        WARN("No data supplied.\n");
        return E_FAIL;
    }

    read_dword(&ptr, &tag);
    TRACE("tag: %s.\n", debugstr_an((const char *)&tag, 4));

    if (tag != TAG_DXBC)
    {
        WARN("Wrong tag.\n");
        return E_FAIL;
    }

    /* checksum? */
    skip_dword_unknown(&ptr, 4);

    skip_dword_unknown(&ptr, 1);

    read_dword(&ptr, &total_size);
    TRACE("total size: %#x\n", total_size);

    if (data_size != total_size)
    {
        WARN("Wrong size supplied.\n");
        return D3DERR_INVALIDCALL;
    }

    read_dword(&ptr, &chunk_count);
    TRACE("chunk count: %#x\n", chunk_count);

    hr = dxbc_init(dxbc, chunk_count);
    if (FAILED(hr))
    {
        WARN("Failed to init dxbc\n");
        return hr;
    }

    for (i = 0; i < chunk_count; ++i)
    {
        DWORD chunk_tag, chunk_size;
        const char *chunk_ptr;
        DWORD chunk_offset;

        read_dword(&ptr, &chunk_offset);
        TRACE("chunk %u at offset %#x\n", i, chunk_offset);

        chunk_ptr = data + chunk_offset;

        read_dword(&chunk_ptr, &chunk_tag);
        read_dword(&chunk_ptr, &chunk_size);

        hr = dxbc_add_section(dxbc, chunk_tag, chunk_ptr, chunk_size);
        if (FAILED(hr))
        {
            WARN("Failed to add section to dxbc\n");
            return hr;
        }
    }

    return hr;
}