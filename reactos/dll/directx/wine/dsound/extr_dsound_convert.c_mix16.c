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
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mix16(SHORT *src, INT *dst, unsigned len)
{
    TRACE("%p - %p %d\n", src, dst, len);
    len /= 2;
    while (len--)
    {
        *dst += le16(*src);
        ++dst; ++src;
    }
}