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
struct ra_d3d11 {size_t vbuf_size; size_t vbuf_used; int /*<<< orphan*/ * vbuf; int /*<<< orphan*/  ctx; int /*<<< orphan*/  dev; } ;
struct ra {struct ra_d3d11* priv; } ;
struct TYPE_6__ {size_t ByteWidth; int /*<<< orphan*/  CPUAccessFlags; int /*<<< orphan*/  BindFlags; int /*<<< orphan*/  Usage; } ;
struct TYPE_5__ {char* pData; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ID3D11Resource ;
typedef  int /*<<< orphan*/  ID3D11Buffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ D3D11_MAPPED_SUBRESOURCE ;
typedef  TYPE_2__ D3D11_BUFFER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_BIND_VERTEX_BUFFER ; 
 int /*<<< orphan*/  D3D11_CPU_ACCESS_WRITE ; 
 int /*<<< orphan*/  D3D11_MAP_WRITE_DISCARD ; 
 int /*<<< orphan*/  D3D11_MAP_WRITE_NO_OVERWRITE ; 
 int /*<<< orphan*/  D3D11_USAGE_DYNAMIC ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_CreateBuffer (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MP_ERR (struct ra*,char*,...) ; 
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int /*<<< orphan*/  mp_HRESULT_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t vbuf_upload(struct ra *ra, void *data, size_t size)
{
    struct ra_d3d11 *p = ra->priv;
    HRESULT hr;

    // Arbitrary size limit in case there is an insane number of vertices
    if (size > 1e9) {
        MP_ERR(ra, "Vertex buffer is too large\n");
        return -1;
    }

    // If the vertex data doesn't fit, realloc the vertex buffer
    if (size > p->vbuf_size) {
        size_t new_size = p->vbuf_size;
        // Arbitrary base size
        if (!new_size)
            new_size = 64 * 1024;
        while (new_size < size)
            new_size *= 2;

        ID3D11Buffer *new_buf;
        D3D11_BUFFER_DESC vbuf_desc = {
            .ByteWidth = new_size,
            .Usage = D3D11_USAGE_DYNAMIC,
            .BindFlags = D3D11_BIND_VERTEX_BUFFER,
            .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
        };
        hr = ID3D11Device_CreateBuffer(p->dev, &vbuf_desc, NULL, &new_buf);
        if (FAILED(hr)) {
            MP_ERR(ra, "Failed to create vertex buffer: %s\n",
                   mp_HRESULT_to_str(hr));
            return -1;
        }

        SAFE_RELEASE(p->vbuf);
        p->vbuf = new_buf;
        p->vbuf_size = new_size;
        p->vbuf_used = 0;
    }

    bool discard = false;
    size_t offset = p->vbuf_used;
    if (offset + size > p->vbuf_size) {
        // We reached the end of the buffer, so discard and wrap around
        discard = true;
        offset = 0;
    }

    D3D11_MAPPED_SUBRESOURCE map = { 0 };
    hr = ID3D11DeviceContext_Map(p->ctx, (ID3D11Resource *)p->vbuf, 0,
        discard ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE,
        0, &map);
    if (FAILED(hr)) {
        MP_ERR(ra, "Failed to map vertex buffer: %s\n", mp_HRESULT_to_str(hr));
        return -1;
    }

    char *cdata = map.pData;
    memcpy(cdata + offset, data, size);

    ID3D11DeviceContext_Unmap(p->ctx, (ID3D11Resource *)p->vbuf, 0);

    p->vbuf_used = offset + size;
    return offset;
}