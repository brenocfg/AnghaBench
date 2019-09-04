#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ServiceName; TYPE_1__* ClientName; } ;
struct TYPE_6__ {scalar_t__ NameType; int NameCount; } ;
struct TYPE_5__ {scalar_t__ NameType; int NameCount; } ;
typedef  TYPE_3__* PKIWI_KERBEROS_TICKET ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ KRB_NT_PRINCIPAL ; 
 scalar_t__ KRB_NT_SRV_HST ; 

BOOL kuhl_m_kerberos_ticket_isLongFilename(PKIWI_KERBEROS_TICKET ticket)
{
	return ticket && (ticket->ClientName) && (ticket->ClientName->NameType == KRB_NT_PRINCIPAL) && (ticket->ClientName->NameCount == 1) && (ticket->ServiceName) && ((ticket->ServiceName->NameType >= KRB_NT_PRINCIPAL) && (ticket->ServiceName->NameType <= KRB_NT_SRV_HST)) && (ticket->ServiceName->NameCount > 1);
}