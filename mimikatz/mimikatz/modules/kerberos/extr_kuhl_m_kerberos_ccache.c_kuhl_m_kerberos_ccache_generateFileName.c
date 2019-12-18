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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {int TicketFlags; TYPE_2__* ServiceName; TYPE_1__* ClientName; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Names; } ;
struct TYPE_6__ {int /*<<< orphan*/ * Names; } ;
typedef  TYPE_3__* PKIWI_KERBEROS_TICKET ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ LocalFree (int /*<<< orphan*/ *) ; 
 int kuhl_m_kerberos_ticket_isLongFilename (TYPE_3__*) ; 
 int /*<<< orphan*/  kull_m_file_cleanFilename (int /*<<< orphan*/ *) ; 
 scalar_t__ swprintf_s (int /*<<< orphan*/ *,size_t,char*,int const,int,char*,...) ; 

wchar_t * kuhl_m_kerberos_ccache_generateFileName(const DWORD index, PKIWI_KERBEROS_TICKET ticket, LPCWSTR ext)
{
	wchar_t * buffer;
	size_t charCount = 0x1000;
	BOOL isLong = kuhl_m_kerberos_ticket_isLongFilename(ticket);

	if(buffer = (wchar_t *) LocalAlloc(LPTR, charCount * sizeof(wchar_t)))
	{
		if(isLong)
			isLong = swprintf_s(buffer, charCount, L"%u-%08x-%wZ@%wZ-%wZ.%s", index, ticket->TicketFlags, &ticket->ClientName->Names[0], &ticket->ServiceName->Names[0], &ticket->ServiceName->Names[1], ext) > 0;
		else
			isLong = swprintf_s(buffer, charCount, L"%u-%08x.%s", index, ticket->TicketFlags, ext) > 0;
		
		if(isLong)
			kull_m_file_cleanFilename(buffer);
		else
			buffer = (wchar_t *) LocalFree(buffer);
	}
	return buffer;
}