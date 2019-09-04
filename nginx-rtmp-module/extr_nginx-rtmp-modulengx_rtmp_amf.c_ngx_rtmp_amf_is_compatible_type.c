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
typedef  scalar_t__ uint8_t ;
typedef  int ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_RTMP_AMF_MIXED_ARRAY ; 
 scalar_t__ NGX_RTMP_AMF_OBJECT ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_amf_is_compatible_type(uint8_t t1, uint8_t t2)
{
    return t1 == t2
        || (t1 == NGX_RTMP_AMF_OBJECT && t2 == NGX_RTMP_AMF_MIXED_ARRAY)
        || (t2 == NGX_RTMP_AMF_OBJECT && t1 == NGX_RTMP_AMF_MIXED_ARRAY);
}