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
struct ao_convert_fmt {scalar_t__ src_fmt; int dst_bits; int pad_msb; } ;

/* Variables and functions */
 scalar_t__ AF_FORMAT_S32 ; 
 int af_fmt_to_bytes (scalar_t__) ; 

__attribute__((used)) static int get_conv_type(struct ao_convert_fmt *fmt)
{
    if (af_fmt_to_bytes(fmt->src_fmt) * 8 == fmt->dst_bits && !fmt->pad_msb)
        return 0; // passthrough
    if (fmt->src_fmt == AF_FORMAT_S32 && fmt->dst_bits == 24 && !fmt->pad_msb)
        return 1; // simple 32->24 bit conversion
    if (fmt->src_fmt == AF_FORMAT_S32 && fmt->dst_bits == 32 && fmt->pad_msb == 8)
        return 2; // simple 32->24 bit conversion, with MSB padding
    return -1; // unsupported
}