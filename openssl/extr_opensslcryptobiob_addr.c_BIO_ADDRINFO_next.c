#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__ const* bai_next; } ;
typedef  TYPE_1__ BIO_ADDRINFO ;

/* Variables and functions */

const BIO_ADDRINFO *BIO_ADDRINFO_next(const BIO_ADDRINFO *bai)
{
    if (bai != NULL)
        return bai->bai_next;
    return NULL;
}