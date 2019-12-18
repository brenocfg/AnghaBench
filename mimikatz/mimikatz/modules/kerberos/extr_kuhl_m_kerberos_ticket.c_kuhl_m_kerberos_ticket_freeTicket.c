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
struct TYPE_4__ {int /*<<< orphan*/  Ticket; int /*<<< orphan*/  Key; int /*<<< orphan*/  Description; int /*<<< orphan*/  AltTargetDomainName; int /*<<< orphan*/  ClientName; int /*<<< orphan*/  TargetDomainName; int /*<<< orphan*/  TargetName; int /*<<< orphan*/  DomainName; int /*<<< orphan*/  ServiceName; } ;
typedef  TYPE_1__* PKIWI_KERBEROS_TICKET ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_freeExternalName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_freeKiwiKerberosBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_freeUnicodeStringBuffer (int /*<<< orphan*/ *) ; 

void kuhl_m_kerberos_ticket_freeTicket(PKIWI_KERBEROS_TICKET ticket)
{
	if(ticket)
	{
		kuhl_m_kerberos_ticket_freeExternalName(ticket->ServiceName);
		kull_m_string_freeUnicodeStringBuffer(&ticket->DomainName);
		kuhl_m_kerberos_ticket_freeExternalName(ticket->TargetName);
		kull_m_string_freeUnicodeStringBuffer(&ticket->TargetDomainName);
		kuhl_m_kerberos_ticket_freeExternalName(ticket->ClientName);
		kull_m_string_freeUnicodeStringBuffer(&ticket->AltTargetDomainName);
		kull_m_string_freeUnicodeStringBuffer(&ticket->Description);
		kuhl_m_kerberos_ticket_freeKiwiKerberosBuffer(&ticket->Key);
		kuhl_m_kerberos_ticket_freeKiwiKerberosBuffer(&ticket->Ticket);
		LocalFree(ticket);
	}
}