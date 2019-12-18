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
struct mp_vdpau_ctx {int dummy; } ;
struct AVBufferRef {int dummy; } ;

/* Variables and functions */
 struct mp_vdpau_ctx* mp_vdpau_get_ctx_from_av (struct AVBufferRef*) ; 
 int mp_vdpau_guess_if_emulated (struct mp_vdpau_ctx*) ; 

__attribute__((used)) static bool is_emulated(struct AVBufferRef *hw_device_ctx)
{
    struct mp_vdpau_ctx *ctx = mp_vdpau_get_ctx_from_av(hw_device_ctx);
    if (!ctx)
        return false;

    return mp_vdpau_guess_if_emulated(ctx);
}