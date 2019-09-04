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
struct ra_hwdec_mapper {struct priv* priv; } ;
struct queue_surf {int busy11; scalar_t__ idle11; } ;
struct priv {int /*<<< orphan*/  ctx11; } ;
typedef  int /*<<< orphan*/  idle ;
typedef  int /*<<< orphan*/  ID3D11Asynchronous ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ASYNC_GETDATA_DONOTFLUSH ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ ID3D11DeviceContext_GetData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ S_FALSE ; 

__attribute__((used)) static bool surf_is_idle11(struct ra_hwdec_mapper *mapper,
                           struct queue_surf *surf)
{
    struct priv *p = mapper->priv;
    HRESULT hr;
    BOOL idle;

    if (!surf->busy11)
        return true;

    hr = ID3D11DeviceContext_GetData(p->ctx11,
        (ID3D11Asynchronous *)surf->idle11, &idle, sizeof(idle),
        D3D11_ASYNC_GETDATA_DONOTFLUSH);
    if (FAILED(hr) || hr == S_FALSE || !idle)
        return false;

    surf->busy11 = false;
    return true;
}