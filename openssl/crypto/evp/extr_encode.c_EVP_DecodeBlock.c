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
 int evp_decodeblock_int (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,int) ; 

int EVP_DecodeBlock(unsigned char *t, const unsigned char *f, int n)
{
    return evp_decodeblock_int(NULL, t, f, n);
}