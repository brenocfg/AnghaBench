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
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bytepad(unsigned char *out, int *out_len,
                   const unsigned char *in1, int in1_len,
                   const unsigned char *in2, int in2_len, int w)
{
    int len;
    unsigned char *p = out;
    int sz = w;

    /* Left encoded w */
    *p++ = 1;
    *p++ = w;
    /* || in1 */
    memcpy(p, in1, in1_len);
    p += in1_len;
    /* [ || in2 ] */
    if (in2 != NULL && in2_len > 0) {
        memcpy(p, in2, in2_len);
        p += in2_len;
    }
    /* Figure out the pad size (divisible by w) */
    len = p - out;
    while (len > sz) {
        sz += w;
    }
    /* zero pad the end of the buffer */
    memset(p, 0, sz - len);
    *out_len = sz;
    return 1;
}