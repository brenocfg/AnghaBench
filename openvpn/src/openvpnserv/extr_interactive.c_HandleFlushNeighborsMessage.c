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
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {scalar_t__ family; TYPE_1__ iface; } ;
typedef  TYPE_2__ flush_neighbors_message_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  FlushIpNetTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushIpNetTable2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD
HandleFlushNeighborsMessage(flush_neighbors_message_t *msg)
{
    if (msg->family == AF_INET)
    {
        return FlushIpNetTable(msg->iface.index);
    }

    return FlushIpNetTable2(msg->family, msg->iface.index);
}