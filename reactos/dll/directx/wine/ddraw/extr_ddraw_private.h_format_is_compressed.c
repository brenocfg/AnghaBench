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
struct TYPE_3__ {int dwFlags; scalar_t__ dwFourCC; } ;
typedef  TYPE_1__ DDPIXELFORMAT ;
typedef  int BOOL ;

/* Variables and functions */
 int DDPF_FOURCC ; 
 scalar_t__ WINED3DFMT_DXT1 ; 
 scalar_t__ WINED3DFMT_DXT2 ; 
 scalar_t__ WINED3DFMT_DXT3 ; 
 scalar_t__ WINED3DFMT_DXT4 ; 
 scalar_t__ WINED3DFMT_DXT5 ; 

__attribute__((used)) static inline BOOL format_is_compressed(const DDPIXELFORMAT *format)
{
    return (format->dwFlags & DDPF_FOURCC) && (format->dwFourCC == WINED3DFMT_DXT1
            || format->dwFourCC == WINED3DFMT_DXT2 || format->dwFourCC == WINED3DFMT_DXT3
            || format->dwFourCC == WINED3DFMT_DXT4 || format->dwFourCC == WINED3DFMT_DXT5);
}