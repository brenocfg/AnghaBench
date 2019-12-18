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
struct TYPE_4__ {int /*<<< orphan*/  maxsize; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * staticbuf; } ;
typedef  TYPE_1__ WPACKET ;

/* Variables and functions */
 int /*<<< orphan*/  maxmaxsize (size_t) ; 
 int wpacket_intern_init_len (TYPE_1__*,int /*<<< orphan*/ ) ; 

int WPACKET_init_null(WPACKET *pkt, size_t lenbytes)
{
    pkt->staticbuf = NULL;
    pkt->buf = NULL;
    pkt->maxsize = maxmaxsize(lenbytes);

    return wpacket_intern_init_len(pkt, 0);
}