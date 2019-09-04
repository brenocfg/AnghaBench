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
 size_t MD2_DIGEST_LENGTH ; 
 scalar_t__ MD2_Final (unsigned char*,void*) ; 

__attribute__((used)) static int md2_final(void *ctx, unsigned char *md, size_t *size)
{
    if (MD2_Final(md, ctx)) {
        *size = MD2_DIGEST_LENGTH;
        return 1;
    }

    return 0;
}