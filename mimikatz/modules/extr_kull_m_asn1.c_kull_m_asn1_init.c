#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ASN1FreeFun_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1FLAGS_NOASSERT ; 
 int /*<<< orphan*/  ASN1_BER_RULE_DER ; 
 int ASN1_CreateDecoder (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ASN1_CreateEncoder (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_CreateModule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char) ; 
 scalar_t__ ASN1_FAILED (int) ; 
 int /*<<< orphan*/  ASN1_THIS_VERSION ; 
 int /*<<< orphan*/ * ASN1dec ; 
 int /*<<< orphan*/ * ASN1enc ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 scalar_t__ hASN1Module ; 
 scalar_t__ kull_m_asn1_encdecfreefntab ; 
 int /*<<< orphan*/  kull_m_asn1_sizetab ; 
 int /*<<< orphan*/  kull_m_asn1_term () ; 

BOOL kull_m_asn1_init()
{
	BOOL status = FALSE;
	int ret;
	if(hASN1Module = ASN1_CreateModule(ASN1_THIS_VERSION, ASN1_BER_RULE_DER, ASN1FLAGS_NOASSERT, 1, kull_m_asn1_encdecfreefntab, kull_m_asn1_encdecfreefntab, (const ASN1FreeFun_t *) kull_m_asn1_encdecfreefntab, kull_m_asn1_sizetab, 'iwik'))
	{
		ret = ASN1_CreateEncoder(hASN1Module, &ASN1enc, NULL, 0, NULL);
		if(ASN1_FAILED(ret))
		{
			PRINT_ERROR(L"ASN1_CreateEncoder: %i\n", ret);
			ASN1enc = NULL;
		}
		else
		{
			ret = ASN1_CreateDecoder(hASN1Module, &ASN1dec, NULL, 0, NULL);
			if(ASN1_FAILED(ret))
			{
				PRINT_ERROR(L"ASN1_CreateDecoder: %i\n", ret);
				ASN1dec = NULL;
			}
		}
	}
	else PRINT_ERROR(L"ASN1_CreateModule\n");

	status = hASN1Module && ASN1enc && ASN1dec;
	if(!status)
		kull_m_asn1_term();
	return status;
}