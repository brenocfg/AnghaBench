#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lwIP_netconn ;
struct TYPE_2__ {int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 int NUM_SOCKETS ; 
 int /*<<< orphan*/  lwIP_ASSERT (int /*<<< orphan*/ *) ; 
 TYPE_1__* sockets ; 

__attribute__((used)) static int alloc_socket(lwIP_netconn *newconn, int accepted)
{
    int i = 0;
    lwIP_ASSERT(newconn);
    /* allocate a new socket identifier */
    for (i = 0; i < NUM_SOCKETS; ++i)
    {
        /* Protect socket array */
        if (!sockets[i].conn)
        {
            sockets[i].conn = newconn;
            return i;
        }
    }
    return -1;
}