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
struct ra_d3d11 {scalar_t__ iqueue; scalar_t__ debug; scalar_t__ ctx; scalar_t__ dev; scalar_t__ dev1; scalar_t__ ctx1; scalar_t__ vbuf; scalar_t__ blit_sampler; scalar_t__ blit_vbuf; scalar_t__ blit_layout; scalar_t__ blit_vs; scalar_t__ blit_float_ps; scalar_t__ clear_cbuf; scalar_t__ clear_vbuf; scalar_t__ clear_layout; scalar_t__ clear_vs; scalar_t__ clear_ps; } ;
struct ra {struct ra_d3d11* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_RLDO_DETAIL ; 
 int /*<<< orphan*/  D3D11_RLDO_SUMMARY ; 
 int /*<<< orphan*/  ID3D11Debug_ReportLiveDeviceObjects (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_ClearState (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Flush (scalar_t__) ; 
 int /*<<< orphan*/  SAFE_RELEASE (scalar_t__) ; 
 int /*<<< orphan*/  debug_marker (struct ra*,char*) ; 
 int /*<<< orphan*/  talloc_free (struct ra*) ; 

__attribute__((used)) static void destroy(struct ra *ra)
{
    struct ra_d3d11 *p = ra->priv;

    // Release everything except the interfaces needed to perform leak checking
    SAFE_RELEASE(p->clear_ps);
    SAFE_RELEASE(p->clear_vs);
    SAFE_RELEASE(p->clear_layout);
    SAFE_RELEASE(p->clear_vbuf);
    SAFE_RELEASE(p->clear_cbuf);
    SAFE_RELEASE(p->blit_float_ps);
    SAFE_RELEASE(p->blit_vs);
    SAFE_RELEASE(p->blit_layout);
    SAFE_RELEASE(p->blit_vbuf);
    SAFE_RELEASE(p->blit_sampler);
    SAFE_RELEASE(p->vbuf);
    SAFE_RELEASE(p->ctx1);
    SAFE_RELEASE(p->dev1);
    SAFE_RELEASE(p->dev);

    if (p->debug && p->ctx) {
        // Destroy the device context synchronously so referenced objects don't
        // show up in the leak check
        ID3D11DeviceContext_ClearState(p->ctx);
        ID3D11DeviceContext_Flush(p->ctx);
    }
    SAFE_RELEASE(p->ctx);

    if (p->debug) {
        // Report any leaked objects
        debug_marker(ra, "after destroy");
        ID3D11Debug_ReportLiveDeviceObjects(p->debug, D3D11_RLDO_DETAIL);
        debug_marker(ra, "after leak check");
        ID3D11Debug_ReportLiveDeviceObjects(p->debug, D3D11_RLDO_SUMMARY);
        debug_marker(ra, "after leak summary");
    }
    SAFE_RELEASE(p->debug);
    SAFE_RELEASE(p->iqueue);

    talloc_free(ra);
}