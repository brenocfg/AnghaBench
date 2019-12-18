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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  float int16_t ;

/* Variables and functions */
 float AV_RN16 (char*) ; 
 int /*<<< orphan*/  AV_WN32 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_float2int (float) ; 

__attribute__((used)) static void bad_hack_mygodwhy(char *data, int samples)
{
    // In reverse, so we can do it in-place.
    for (int n = samples - 1; n >= 0; n--) {
        int16_t val = AV_RN16(data + n * 2);
        float fval = val / (float)(1 << 15);
        uint32_t ival = av_float2int(fval);
        AV_WN32(data + n * 4, ival);
    }
}