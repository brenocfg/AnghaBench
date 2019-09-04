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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (double*,char const*,int) ; 

double
AMF_DecodeNumber(const char *data)
{
    double dVal;
#if __FLOAT_WORD_ORDER == __BYTE_ORDER
#if __BYTE_ORDER == __BIG_ENDIAN
    memcpy(&dVal, data, 8);
#elif __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned char *ci, *co;
    ci = (unsigned char *)data;
    co = (unsigned char *)&dVal;
    co[0] = ci[7];
    co[1] = ci[6];
    co[2] = ci[5];
    co[3] = ci[4];
    co[4] = ci[3];
    co[5] = ci[2];
    co[6] = ci[1];
    co[7] = ci[0];
#endif
#else
#if __BYTE_ORDER == __LITTLE_ENDIAN	/* __FLOAT_WORD_ORER == __BIG_ENDIAN */
    unsigned char *ci, *co;
    ci = (unsigned char *)data;
    co = (unsigned char *)&dVal;
    co[0] = ci[3];
    co[1] = ci[2];
    co[2] = ci[1];
    co[3] = ci[0];
    co[4] = ci[7];
    co[5] = ci[6];
    co[6] = ci[5];
    co[7] = ci[4];
#else /* __BYTE_ORDER == __BIG_ENDIAN && __FLOAT_WORD_ORER == __LITTLE_ENDIAN */
    unsigned char *ci, *co;
    ci = (unsigned char *)data;
    co = (unsigned char *)&dVal;
    co[0] = ci[4];
    co[1] = ci[5];
    co[2] = ci[6];
    co[3] = ci[7];
    co[4] = ci[0];
    co[5] = ci[1];
    co[6] = ci[2];
    co[7] = ci[3];
#endif
#endif
    return dVal;
}