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
typedef  int /*<<< orphan*/  PACMDRVSTREAMINSTANCE ;
typedef  int* LPDWORD ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  W16 (unsigned char*,short) ; 
 int min (int,int) ; 
 short ulaw2linear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvtXXulaw16K(PACMDRVSTREAMINSTANCE adsi,
                         const unsigned char* src, LPDWORD srcsize,
                         unsigned char* dst, LPDWORD dstsize)
{
    DWORD       len = min(*srcsize, *dstsize / 2);
    DWORD       i;
    short       w;

    *srcsize = len;
    *dstsize = len * 2;
    for (i = 0; i < len; i++)
    {
        w = ulaw2linear(*src++);
        W16(dst, w);    dst += 2;
    }
}