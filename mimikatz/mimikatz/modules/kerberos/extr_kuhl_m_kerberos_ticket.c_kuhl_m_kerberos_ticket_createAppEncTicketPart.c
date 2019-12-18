#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_val; } ;
struct TYPE_8__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Value; } ;
struct TYPE_9__ {int /*<<< orphan*/  RenewUntil; int /*<<< orphan*/  EndTime; int /*<<< orphan*/  StartTime; int /*<<< orphan*/  ClientName; int /*<<< orphan*/  AltTargetDomainName; TYPE_1__ Key; int /*<<< orphan*/  KeyType; int /*<<< orphan*/  TicketFlags; } ;
typedef  TYPE_2__* PKIWI_KERBEROS_TICKET ;
typedef  TYPE_3__* PBERVAL ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  ID_APP_ENCTICKETPART ; 
 int /*<<< orphan*/  ID_AUTHDATA_AD_IF_RELEVANT ; 
 int /*<<< orphan*/  ID_AUTHDATA_AD_WIN2K_PAC ; 
 int /*<<< orphan*/  ID_CTX_AUTHORIZATIONDATA_AD_DATA ; 
 int /*<<< orphan*/  ID_CTX_AUTHORIZATIONDATA_AD_TYPE ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_AUTHORIZATION_DATA ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_AUTHTIME ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_CNAME ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_CREALM ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_ENDTIME ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_FLAGS ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_KEY ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_RENEW_TILL ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_STARTTIME ; 
 int /*<<< orphan*/  ID_CTX_ENCTICKETPART_TRANSITED ; 
 int /*<<< orphan*/  ID_CTX_TRANSITEDENCODING_CONTENTS ; 
 int /*<<< orphan*/  ID_CTX_TRANSITEDENCODING_TR_TYPE ; 
 int /*<<< orphan*/  LBER_USE_DER ; 
 int /*<<< orphan*/  MAKE_APP_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_CTX_TAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ber_alloc_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ber_bvfree (TYPE_3__*) ; 
 scalar_t__ ber_flatten (int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  ber_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_createSequenceEncryptionKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_createSequencePrimaryName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_asn1_BitStringFromULONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_asn1_GenString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_asn1_GenTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PBERVAL kuhl_m_kerberos_ticket_createAppEncTicketPart(PKIWI_KERBEROS_TICKET ticket, LPCVOID PacAuthData, DWORD PacAuthDataSize)
{
	BerElement *pBer, *pBerPac;
	PBERVAL pBerVal = NULL, pBerValPac = NULL;
	if(pBer = ber_alloc_t(LBER_USE_DER))
	{
		ber_printf(pBer, "t{{t{", MAKE_APP_TAG(ID_APP_ENCTICKETPART), MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_FLAGS));
		kull_m_asn1_BitStringFromULONG(pBer, ticket->TicketFlags);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_KEY));
		kuhl_m_kerberos_ticket_createSequenceEncryptionKey(pBer, ticket->KeyType, ticket->Key.Value, ticket->Key.Length);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_CREALM));
		kull_m_asn1_GenString(pBer, &ticket->AltTargetDomainName);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_CNAME));
		kuhl_m_kerberos_ticket_createSequencePrimaryName(pBer, ticket->ClientName);
		ber_printf(pBer, "}t{{t{i}t{o}}}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_TRANSITED), MAKE_CTX_TAG(ID_CTX_TRANSITEDENCODING_TR_TYPE), 0, MAKE_CTX_TAG(ID_CTX_TRANSITEDENCODING_CONTENTS), NULL, 0, MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_AUTHTIME));
		kull_m_asn1_GenTime(pBer, &ticket->StartTime);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_STARTTIME));
		kull_m_asn1_GenTime(pBer, &ticket->StartTime);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_ENDTIME));
		kull_m_asn1_GenTime(pBer, &ticket->EndTime);
		ber_printf(pBer, "}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_RENEW_TILL));
		kull_m_asn1_GenTime(pBer, &ticket->RenewUntil);
		ber_printf(pBer, "}"); /* ID_CTX_ENCTICKETPART_CADDR not present */
		if(PacAuthData && PacAuthDataSize)
		{
			ber_printf(pBer, "t{{{t{i}t{", MAKE_CTX_TAG(ID_CTX_ENCTICKETPART_AUTHORIZATION_DATA), MAKE_CTX_TAG(ID_CTX_AUTHORIZATIONDATA_AD_TYPE), ID_AUTHDATA_AD_IF_RELEVANT, MAKE_CTX_TAG(ID_CTX_AUTHORIZATIONDATA_AD_DATA));
			if(pBerPac = ber_alloc_t(LBER_USE_DER))
			{
				ber_printf(pBerPac, "{{t{i}t{o}}}", MAKE_CTX_TAG(ID_CTX_AUTHORIZATIONDATA_AD_TYPE), ID_AUTHDATA_AD_WIN2K_PAC, MAKE_CTX_TAG(ID_CTX_AUTHORIZATIONDATA_AD_DATA), PacAuthData, PacAuthDataSize);
				if(ber_flatten(pBerPac, &pBerValPac) >= 0)
					ber_printf(pBer, "o", pBerValPac->bv_val, pBerValPac->bv_len);
				ber_free(pBerPac, 1);
			}
			ber_printf(pBer, "}}}}");
		}
		ber_printf(pBer, "}}");
		ber_flatten(pBer, &pBerVal);
		if(pBerValPac)
			ber_bvfree(pBerValPac);
		ber_free(pBer, 1);
	}
	return pBerVal;
}