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
 int /*<<< orphan*/  ASN1_FreeEncoded (scalar_t__,void*) ; 
 scalar_t__ ASN1enc ; 

void kull_m_asn1_freeEnc(void *pBuf)
{
	if(ASN1enc && pBuf)
		ASN1_FreeEncoded(ASN1enc, pBuf);
}