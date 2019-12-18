#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dwBumpLuminanceBitMask; int /*<<< orphan*/  dwBBitMask; } ;
struct TYPE_11__ {int /*<<< orphan*/  dwBumpDvBitMask; int /*<<< orphan*/  dwGBitMask; } ;
struct TYPE_10__ {int /*<<< orphan*/  dwBumpDuBitMask; int /*<<< orphan*/  dwRBitMask; } ;
struct TYPE_9__ {int /*<<< orphan*/  dwBumpBitCount; int /*<<< orphan*/  dwAlphaBitDepth; int /*<<< orphan*/  dwZBufferBitDepth; int /*<<< orphan*/  dwRGBBitCount; int /*<<< orphan*/  dwYUVBitCount; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwRGBZBitMask; int /*<<< orphan*/  dwRGBAlphaBitMask; } ;
struct TYPE_13__ {int dwFlags; int dwFourCC; TYPE_5__ u4; TYPE_4__ u3; TYPE_3__ u2; TYPE_2__ u1; TYPE_1__ u5; } ;
typedef  TYPE_6__ DDPIXELFORMAT ;

/* Variables and functions */
 int DDPF_ALPHA ; 
 int DDPF_ALPHAPIXELS ; 
 int DDPF_BUMPDUDV ; 
 int DDPF_FOURCC ; 
 int DDPF_RGB ; 
 int DDPF_ZBUFFER ; 
 int DDPF_ZPIXELS ; 
 int /*<<< orphan*/  DDRAW_dump_pixelformat_flag (int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static void
DDRAW_dump_pixelformat(const DDPIXELFORMAT *pf)
{
    TRACE("( ");
    DDRAW_dump_pixelformat_flag(pf->dwFlags);
    if (pf->dwFlags & DDPF_FOURCC)
        TRACE(", dwFourCC code '%c%c%c%c' (0x%08x) - %u bits per pixel",
                (unsigned char)( pf->dwFourCC     &0xff),
                (unsigned char)((pf->dwFourCC>> 8)&0xff),
                (unsigned char)((pf->dwFourCC>>16)&0xff),
                (unsigned char)((pf->dwFourCC>>24)&0xff),
                pf->dwFourCC,
                pf->u1.dwYUVBitCount);
    if (pf->dwFlags & DDPF_RGB)
    {
        TRACE(", RGB bits: %u, R 0x%08x G 0x%08x B 0x%08x",
                pf->u1.dwRGBBitCount,
                pf->u2.dwRBitMask,
                pf->u3.dwGBitMask,
                pf->u4.dwBBitMask);
        if (pf->dwFlags & DDPF_ALPHAPIXELS)
            TRACE(" A 0x%08x", pf->u5.dwRGBAlphaBitMask);
        if (pf->dwFlags & DDPF_ZPIXELS)
            TRACE(" Z 0x%08x", pf->u5.dwRGBZBitMask);
    }
    if (pf->dwFlags & DDPF_ZBUFFER)
        TRACE(", Z bits: %u", pf->u1.dwZBufferBitDepth);
    if (pf->dwFlags & DDPF_ALPHA)
        TRACE(", Alpha bits: %u", pf->u1.dwAlphaBitDepth);
    if (pf->dwFlags & DDPF_BUMPDUDV)
        TRACE(", Bump bits: %u, U 0x%08x V 0x%08x L 0x%08x",
                pf->u1.dwBumpBitCount,
                pf->u2.dwBumpDuBitMask,
                pf->u3.dwBumpDvBitMask,
                pf->u4.dwBumpLuminanceBitMask);
    TRACE(")\n");
}