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
typedef  int wchar_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 unsigned char** page_uni2charset ; 

__attribute__((used)) static int uni2char(wchar_t uni, unsigned char *out, int boundlen)
{
    unsigned char *uni2charset;
    unsigned char cl = uni & 0x00ff;
    unsigned char ch = (uni & 0xff00) >> 8;

    if (boundlen <= 0)
        return -ENAMETOOLONG;

    uni2charset = page_uni2charset[ch];
    if (uni2charset && uni2charset[cl])
        out[0] = uni2charset[cl];
    else
        return -EINVAL;
    return 1;
}