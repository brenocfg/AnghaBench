#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dxbc {int count; TYPE_1__* sections; } ;
struct TYPE_2__ {int data_size; int tag; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCreateBlob (int,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 char* ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int TAG_DXBC ; 
 int /*<<< orphan*/  TRACE (char*,struct dxbc*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_dword (char**,int) ; 
 int /*<<< orphan*/  write_dword_unknown (char**,int) ; 

HRESULT dxbc_write_blob(struct dxbc *dxbc, ID3DBlob **blob)
{
    DWORD size = 32, offset = size + 4 * dxbc->count;
    ID3DBlob *object;
    HRESULT hr;
    char *ptr;
    unsigned int i;

    TRACE("dxbc %p, blob %p.\n", dxbc, blob);

    for (i = 0; i < dxbc->count; ++i)
    {
        size += 12 + dxbc->sections[i].data_size;
    }

    hr = D3DCreateBlob(size, &object);
    if (FAILED(hr))
    {
        WARN("Failed to create blob\n");
        return hr;
    }

    ptr = ID3D10Blob_GetBufferPointer(object);

    write_dword(&ptr, TAG_DXBC);

    /* signature(?) */
    write_dword_unknown(&ptr, 0);
    write_dword_unknown(&ptr, 0);
    write_dword_unknown(&ptr, 0);
    write_dword_unknown(&ptr, 0);

    /* seems to be always 1 */
    write_dword_unknown(&ptr, 1);

    /* DXBC size */
    write_dword(&ptr, size);

    /* chunk count */
    write_dword(&ptr, dxbc->count);

    /* write the chunk offsets */
    for (i = 0; i < dxbc->count; ++i)
    {
        write_dword(&ptr, offset);
        offset += 8 + dxbc->sections[i].data_size;
    }

    /* write the chunks */
    for (i = 0; i < dxbc->count; ++i)
    {
        write_dword(&ptr, dxbc->sections[i].tag);
        write_dword(&ptr, dxbc->sections[i].data_size);
        memcpy(ptr, dxbc->sections[i].data, dxbc->sections[i].data_size);
        ptr += dxbc->sections[i].data_size;
    }

    TRACE("Created ID3DBlob %p\n", object);

    *blob = object;

    return S_OK;
}