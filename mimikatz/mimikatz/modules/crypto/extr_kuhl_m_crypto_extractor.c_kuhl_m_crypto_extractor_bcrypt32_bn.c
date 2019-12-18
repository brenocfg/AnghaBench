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
struct TYPE_7__ {int tag; scalar_t__ size; } ;
struct TYPE_9__ {TYPE_2__ bn; } ;
struct TYPE_8__ {TYPE_2__ bn; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PKIWI_BCRYPT_BIGNUM_Int32 ;
typedef  TYPE_2__* PKIWI_BCRYPT_BIGNUM_Header ;
typedef  TYPE_3__* PKIWI_BCRYPT_BIGNUM_Div ;
typedef  TYPE_4__* PKIWI_BCRYPT_BIGNUM_ComplexType32 ;

/* Variables and functions */
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KIWI_BCRYPT_BIGNUM_Int32 ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void kuhl_m_crypto_extractor_bcrypt32_bn(PKIWI_BCRYPT_BIGNUM_Header bn)
{
	if(bn->tag)
	{
		switch(((bn->tag) >> 16) & 0xff)
		{
		case 'I':
			kull_m_string_wprintf_hex(((PKIWI_BCRYPT_BIGNUM_Int32) bn)->data, bn->size - FIELD_OFFSET(KIWI_BCRYPT_BIGNUM_Int32, data), 0);
			break;
		case 'D':
			kuhl_m_crypto_extractor_bcrypt32_bn(&((PKIWI_BCRYPT_BIGNUM_Div) bn)->bn);
			break;
		case 'M':
			kuhl_m_crypto_extractor_bcrypt32_bn(&((PKIWI_BCRYPT_BIGNUM_ComplexType32) bn)->bn);
			break;
		default:
			PRINT_ERROR(L"Unknown tag: %08x\n", bn->tag);
		}
	}
}