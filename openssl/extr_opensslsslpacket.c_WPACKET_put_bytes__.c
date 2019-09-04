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
typedef  int /*<<< orphan*/  WPACKET ;

/* Variables and functions */
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  put_value (unsigned char*,unsigned int,size_t) ; 

int WPACKET_put_bytes__(WPACKET *pkt, unsigned int val, size_t size)
{
    unsigned char *data;

    /* Internal API, so should not fail */
    if (!ossl_assert(size <= sizeof(unsigned int))
            || !WPACKET_allocate_bytes(pkt, size, &data)
            || !put_value(data, val, size))
        return 0;

    return 1;
}