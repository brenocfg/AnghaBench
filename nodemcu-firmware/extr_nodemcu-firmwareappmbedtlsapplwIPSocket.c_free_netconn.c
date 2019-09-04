#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ readbuf; } ;
typedef  TYPE_1__ lwIP_netconn ;

/* Variables and functions */
 int /*<<< orphan*/  lwIP_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ringbuf_free (scalar_t__*) ; 

__attribute__((used)) static void free_netconn(lwIP_netconn *netconn)
{
    lwIP_ASSERT(netconn);
    if (netconn->readbuf)
    {
        ringbuf_free(&netconn->readbuf);
    }

    os_free(netconn);
    netconn = NULL;
}