#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t lenbytes; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ WPACKET_SUB ;
struct TYPE_5__ {size_t written; size_t maxsize; TYPE_1__* subs; } ;
typedef  TYPE_2__ WPACKET ;

/* Variables and functions */
 size_t maxmaxsize (size_t) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

int WPACKET_set_max_size(WPACKET *pkt, size_t maxsize)
{
    WPACKET_SUB *sub;
    size_t lenbytes;

    /* Internal API, so should not fail */
    if (!ossl_assert(pkt->subs != NULL))
        return 0;

    /* Find the WPACKET_SUB for the top level */
    for (sub = pkt->subs; sub->parent != NULL; sub = sub->parent)
        continue;

    lenbytes = sub->lenbytes;
    if (lenbytes == 0)
        lenbytes = sizeof(pkt->maxsize);

    if (maxmaxsize(lenbytes) < maxsize || maxsize < pkt->written)
        return 0;

    pkt->maxsize = maxsize;

    return 1;
}