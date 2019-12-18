#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Length; scalar_t__ Value; } ;
struct TYPE_7__ {int /*<<< orphan*/  Length; scalar_t__ Value; } ;
struct TYPE_6__ {scalar_t__ Buffer; } ;
struct TYPE_9__ {TYPE_3__ Ticket; int /*<<< orphan*/  TicketKvno; int /*<<< orphan*/  TicketEncType; TYPE_2__ Key; int /*<<< orphan*/  KeyType; int /*<<< orphan*/  TicketFlags; TYPE_1__ Description; int /*<<< orphan*/  AltTargetDomainName; int /*<<< orphan*/  ClientName; int /*<<< orphan*/  TargetDomainName; int /*<<< orphan*/  TargetName; int /*<<< orphan*/  DomainName; int /*<<< orphan*/  ServiceName; int /*<<< orphan*/  RenewUntil; int /*<<< orphan*/  EndTime; int /*<<< orphan*/  StartTime; } ;
typedef  TYPE_4__* PKIWI_KERBEROS_TICKET ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_displayExternalName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_displayFlags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_etype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_displayLocalFileTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,int /*<<< orphan*/ ,int) ; 

void kuhl_m_kerberos_ticket_display(PKIWI_KERBEROS_TICKET ticket, BOOL withKey, BOOL encodedTicketToo)
{
	kprintf(L"\n\t   Start/End/MaxRenew: ");
	kull_m_string_displayLocalFileTime(&ticket->StartTime); kprintf(L" ; ");
	kull_m_string_displayLocalFileTime(&ticket->EndTime); kprintf(L" ; ");
	kull_m_string_displayLocalFileTime(&ticket->RenewUntil);

	kuhl_m_kerberos_ticket_displayExternalName(L"\n\t   Service Name ", ticket->ServiceName, &ticket->DomainName);
	kuhl_m_kerberos_ticket_displayExternalName(L"\n\t   Target Name  ", ticket->TargetName, &ticket->TargetDomainName);
	kuhl_m_kerberos_ticket_displayExternalName(L"\n\t   Client Name  ", ticket->ClientName, &ticket->AltTargetDomainName);
	if(ticket->Description.Buffer)
		kprintf(L" ( %wZ )", &ticket->Description);
	kprintf(L"\n\t   Flags %08x    : ", ticket->TicketFlags);
	kuhl_m_kerberos_ticket_displayFlags(ticket->TicketFlags);
	if(withKey)
	{
		kprintf(L"\n\t   Session Key       : 0x%08x - %s", ticket->KeyType, kuhl_m_kerberos_ticket_etype(ticket->KeyType));
		if(ticket->Key.Value)
		{
			kprintf(L"\n\t     ");
			kull_m_string_wprintf_hex(ticket->Key.Value, ticket->Key.Length, 0);
		}
	}
	kprintf(L"\n\t   Ticket            : 0x%08x - %s ; kvno = %u", ticket->TicketEncType, kuhl_m_kerberos_ticket_etype(ticket->TicketEncType), ticket->TicketKvno);
	
	if(encodedTicketToo)
	{
		kprintf(L"\n\t     ");
		if(ticket->Ticket.Value)
			kull_m_string_wprintf_hex(ticket->Ticket.Value, ticket->Ticket.Length, 1);
		else PRINT_ERROR_AUTO(L"NULL Ticket Value !");
	}
	else kprintf(L"\t[...]");
}