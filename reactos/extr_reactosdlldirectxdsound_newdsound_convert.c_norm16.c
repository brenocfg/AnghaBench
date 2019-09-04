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
typedef  int /*<<< orphan*/  SHORT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  le16 (int) ; 

__attribute__((used)) static void norm16(INT *src, SHORT *dst, unsigned len)
{
    TRACE("%p - %p %d\n", src, dst, len);
    len /= 2;
    while (len--)
    {
        *dst = le16(*src);
        if (*src <= -0x8000)
            *dst = le16(0x8000);
        else if (*src > 0x7fff)
            *dst = le16(0x7fff);
        ++dst;
        ++src;
    }
}