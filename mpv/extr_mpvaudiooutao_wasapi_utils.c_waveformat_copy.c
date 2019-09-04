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
struct TYPE_6__ {scalar_t__ wFormatTag; } ;
struct TYPE_5__ {TYPE_2__ Format; } ;
typedef  TYPE_1__ WAVEFORMATEXTENSIBLE ;
typedef  TYPE_2__ WAVEFORMATEX ;

/* Variables and functions */
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 

__attribute__((used)) static void waveformat_copy(WAVEFORMATEXTENSIBLE* dst, WAVEFORMATEX* src)
{
    if (src->wFormatTag == WAVE_FORMAT_EXTENSIBLE) {
        *dst = *(WAVEFORMATEXTENSIBLE *)src;
    } else {
        dst->Format = *src;
    }
}