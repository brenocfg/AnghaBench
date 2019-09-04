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
 int INT_MAX ; 

int ASN1_object_size(int constructed, int length, int tag)
{
    int ret = 1;
    if (length < 0)
        return -1;
    if (tag >= 31) {
        while (tag > 0) {
            tag >>= 7;
            ret++;
        }
    }
    if (constructed == 2) {
        ret += 3;
    } else {
        ret++;
        if (length > 127) {
            int tmplen = length;
            while (tmplen > 0) {
                tmplen >>= 8;
                ret++;
            }
        }
    }
    if (ret >= INT_MAX - length)
        return -1;
    return ret + length;
}