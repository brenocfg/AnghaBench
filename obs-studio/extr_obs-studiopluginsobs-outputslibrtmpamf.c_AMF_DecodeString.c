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
struct TYPE_3__ {scalar_t__ av_len; char* av_val; } ;
typedef  TYPE_1__ AVal ;

/* Variables and functions */
 scalar_t__ AMF_DecodeInt16 (char const*) ; 

void
AMF_DecodeString(const char *data, AVal *bv)
{
    bv->av_len = AMF_DecodeInt16(data);
    bv->av_val = (bv->av_len > 0) ? (char *)data + 2 : NULL;
}