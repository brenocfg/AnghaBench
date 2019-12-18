#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_val; } ;
struct TYPE_10__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Value; } ;
struct TYPE_9__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Value; } ;
struct TYPE_11__ {int /*<<< orphan*/  ServiceName; int /*<<< orphan*/  DomainName; int /*<<< orphan*/  RenewUntil; int /*<<< orphan*/  EndTime; int /*<<< orphan*/  StartTime; int /*<<< orphan*/  TicketFlags; int /*<<< orphan*/  ClientName; int /*<<< orphan*/  AltTargetDomainName; TYPE_2__ Key; int /*<<< orphan*/  KeyType; TYPE_1__ Ticket; int /*<<< orphan*/  TicketKvno; int /*<<< orphan*/  TicketEncType; } ;
typedef  TYPE_3__* PKIWI_KERBEROS_TICKET ;
typedef  TYPE_4__* PBERVAL ;
typedef  int /*<<< orphan*/  BerElement ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY_ASN1_ID_SEQUENCE ; 
 int /*<<< orphan*/  ID_APP_ENCKRBCREDPART ; 
 int /*<<< orphan*/  ID_APP_KRB_CRED ; 
 int /*<<< orphan*/  ID_APP_TICKET ; 
 int /*<<< orphan*/  ID_CTX_ENCKRBCREDPART_TICKET_INFO ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_ENDTIME ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_FLAGS ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_KEY ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_PNAME ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_PREALM ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_RENEW_TILL ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_SNAME ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_SREAL ; 
 int /*<<< orphan*/  ID_CTX_KRBCREDINFO_STARTTIME ; 
 int /*<<< orphan*/  ID_CTX_KRB_CRED_ENC_PART ; 
 int /*<<< orphan*/  ID_CTX_KRB_CRED_MSG_TYPE ; 
 int /*<<< orphan*/  ID_CTX_KRB_CRED_PVNO ; 
 int /*<<< orphan*/  ID_CTX_KRB_CRED_TICKETS ; 
 int /*<<< orphan*/  ID_CTX_TICKET_ENC_PART ; 
 int /*<<< orphan*/  ID_CTX_TICKET_REALM ; 
 int /*<<< orphan*/  ID_CTX_TICKET_SNAME ; 
 int /*<<< orphan*/  ID_CTX_TICKET_TKT_VNO ; 
 int /*<<< orphan*/  KERBEROS_VERSION ; 
 int /*<<< orphan*/  KERB_ETYPE_NULL ; 
 int /*<<< orphan*/  LBER_USE_DER ; 
 int /*<<< orphan*/  MAKE_APP_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_CTX_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ber_alloc_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_bvfree (TYPE_4__*) ; 
 scalar_t__ ber_flatten (int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  ber_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_createSequenceEncryptedData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_createSequenceEncryptionKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_createSequencePrimaryName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_asn1_BitStringFromULONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_asn1_GenString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_asn1_GenTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PBERVAL kuhl_m_kerberos_ticket_createAppKrbCred(PKIWI_KERBEROS_TICKET ticket, BOOL valueIsTicket)
{
	BerElement *pBer, *pBerApp;
	PBERVAL pBerVal = NULL, pBerVallApp = NULL;
	if(pBer = ber_alloc_t(LBER_USE_DER))
	{
		ber_printf(pBer, "t{{t{i}t{i}t{", MAKE_APP_TAG(ID_APP_KRB_CRED), MAKE_CTX_TAG(ID_CTX_KRB_CRED_PVNO), KERBEROS_VERSION, MAKE_CTX_TAG(ID_CTX_KRB_CRED_MSG_TYPE), ID_APP_KRB_CRED, MAKE_CTX_TAG(ID_CTX_KRB_CRED_TICKETS));
		if(!valueIsTicket)
		{
			ber_printf(pBer, "{t{{t{i}t{", MAKE_APP_TAG(ID_APP_TICKET), MAKE_CTX_TAG(ID_CTX_TICKET_TKT_VNO), KERBEROS_VERSION, MAKE_CTX_TAG(ID_CTX_TICKET_REALM));
			kull_m_asn1_GenString(pBer, &ticket->DomainName);
			ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_TICKET_SNAME));
			kuhl_m_kerberos_ticket_createSequencePrimaryName(pBer, ticket->ServiceName);
			ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_TICKET_ENC_PART));
			kuhl_m_kerberos_ticket_createSequenceEncryptedData(pBer, ticket->TicketEncType, ticket->TicketKvno, ticket->Ticket.Value, ticket->Ticket.Length);
			ber_printf(pBer, "}}}}");
		}
		else ber_printf(pBer, "to", DIRTY_ASN1_ID_SEQUENCE, ticket->Ticket.Value, ticket->Ticket.Length);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_KRB_CRED_ENC_PART));
		if(pBerApp = ber_alloc_t(LBER_USE_DER))
		{
			ber_printf(pBerApp, "t{{t{{{t{", MAKE_APP_TAG(ID_APP_ENCKRBCREDPART), MAKE_CTX_TAG(ID_CTX_ENCKRBCREDPART_TICKET_INFO), MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_KEY));
			kuhl_m_kerberos_ticket_createSequenceEncryptionKey(pBerApp, ticket->KeyType, ticket->Key.Value, ticket->Key.Length);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_PREALM));
			kull_m_asn1_GenString(pBerApp, &ticket->AltTargetDomainName);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_PNAME));
			kuhl_m_kerberos_ticket_createSequencePrimaryName(pBerApp, ticket->ClientName);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_FLAGS));
			kull_m_asn1_BitStringFromULONG(pBerApp, ticket->TicketFlags);	/* ID_CTX_KRBCREDINFO_AUTHTIME not present */
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_STARTTIME));
			kull_m_asn1_GenTime(pBerApp, &ticket->StartTime);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_ENDTIME));
			kull_m_asn1_GenTime(pBerApp, &ticket->EndTime);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_RENEW_TILL));
			kull_m_asn1_GenTime(pBerApp, &ticket->RenewUntil);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_SREAL));
			kull_m_asn1_GenString(pBerApp, &ticket->DomainName);
			ber_printf(pBerApp, "}t{", MAKE_CTX_TAG(ID_CTX_KRBCREDINFO_SNAME));
			kuhl_m_kerberos_ticket_createSequencePrimaryName(pBerApp, ticket->ServiceName);
			ber_printf(pBerApp, "}}}}}}");

			if(ber_flatten(pBerApp, &pBerVallApp) >= 0)
				kuhl_m_kerberos_ticket_createSequenceEncryptedData(pBer, KERB_ETYPE_NULL, 0, pBerVallApp->bv_val, pBerVallApp->bv_len);
			ber_free(pBerApp, 1);
		}
		ber_printf(pBer, "}}}");
		ber_flatten(pBer, &pBerVal);
		if(pBerVallApp)
			ber_bvfree(pBerVallApp);
		ber_free(pBer, 1);
	}
	return pBerVal;
}