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

/* Variables and functions */
 int /*<<< orphan*/  ASN1_CloseDecoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_CloseEncoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_CloseModule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1dec ; 
 int /*<<< orphan*/ * ASN1enc ; 
 int /*<<< orphan*/ * hASN1Module ; 

void kull_m_asn1_term()
{
	if(ASN1dec)
	{
		ASN1_CloseDecoder(ASN1dec);
		ASN1dec = NULL;
	}
	if(ASN1enc)
	{
		ASN1_CloseEncoder(ASN1enc);
		ASN1enc = NULL;
	}
	if(hASN1Module)
	{
		ASN1_CloseModule(hASN1Module);
		hASN1Module = NULL;
	}
}