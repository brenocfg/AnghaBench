#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * rootPtr; } ;
struct TYPE_7__ {TYPE_1__ snziNodeOrRoot; } ;
typedef  TYPE_2__ ptw32_oll_ticket_t ;
struct TYPE_8__ {int /*<<< orphan*/  proxyRoot; } ;
typedef  TYPE_3__ ptw32_oll_csnzi_t ;

/* Variables and functions */

ptw32_oll_ticket_t
ptw32_oll_DirectTicket(ptw32_oll_csnzi_t* csnziPtr)
{
  ptw32_oll_ticket_t ticket;
  ticket.snziNodeOrRoot.rootPtr = &csnziPtr->proxyRoot;
  return ticket;
}