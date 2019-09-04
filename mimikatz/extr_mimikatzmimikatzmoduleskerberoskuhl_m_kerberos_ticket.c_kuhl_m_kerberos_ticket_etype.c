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
typedef  char* PCWCHAR ;
typedef  int LONG ;

/* Variables and functions */
#define  KERB_ETYPE_AES128_CTS_HMAC_SHA1_96 149 
#define  KERB_ETYPE_AES128_CTS_HMAC_SHA1_96_PLAIN 148 
#define  KERB_ETYPE_AES256_CTS_HMAC_SHA1_96 147 
#define  KERB_ETYPE_AES256_CTS_HMAC_SHA1_96_PLAIN 146 
#define  KERB_ETYPE_DES_CBC_CRC 145 
#define  KERB_ETYPE_DES_CBC_MD4 144 
#define  KERB_ETYPE_DES_CBC_MD5 143 
#define  KERB_ETYPE_DES_CBC_MD5_NT 142 
#define  KERB_ETYPE_DES_PLAIN 141 
#define  KERB_ETYPE_NULL 140 
#define  KERB_ETYPE_RC4_HMAC_NT 139 
#define  KERB_ETYPE_RC4_HMAC_NT_EXP 138 
#define  KERB_ETYPE_RC4_HMAC_OLD 137 
#define  KERB_ETYPE_RC4_HMAC_OLD_EXP 136 
#define  KERB_ETYPE_RC4_LM 135 
#define  KERB_ETYPE_RC4_MD4 134 
#define  KERB_ETYPE_RC4_PLAIN 133 
#define  KERB_ETYPE_RC4_PLAIN2 132 
#define  KERB_ETYPE_RC4_PLAIN_EXP 131 
#define  KERB_ETYPE_RC4_PLAIN_OLD 130 
#define  KERB_ETYPE_RC4_PLAIN_OLD_EXP 129 
#define  KERB_ETYPE_RC4_SHA 128 

PCWCHAR kuhl_m_kerberos_ticket_etype(LONG eType)
{
	PCWCHAR type;
	switch(eType)
	{
	case KERB_ETYPE_NULL:							type = L"null             "; break;
	case KERB_ETYPE_DES_PLAIN:						type = L"des_plain        "; break;
	case KERB_ETYPE_DES_CBC_CRC:					type = L"des_cbc_crc      "; break;
	case KERB_ETYPE_DES_CBC_MD4:					type = L"des_cbc_md4      "; break;
	case KERB_ETYPE_DES_CBC_MD5:					type = L"des_cbc_md5      "; break;
	case KERB_ETYPE_DES_CBC_MD5_NT:					type = L"des_cbc_md5_nt   "; break;
	case KERB_ETYPE_RC4_PLAIN:						type = L"rc4_plain        "; break;
	case KERB_ETYPE_RC4_PLAIN2:						type = L"rc4_plain2       "; break;
	case KERB_ETYPE_RC4_PLAIN_EXP:					type = L"rc4_plain_exp    "; break;
	case KERB_ETYPE_RC4_LM:							type = L"rc4_lm           "; break;
	case KERB_ETYPE_RC4_MD4:						type = L"rc4_md4          "; break;
	case KERB_ETYPE_RC4_SHA:						type = L"rc4_sha          "; break;
	case KERB_ETYPE_RC4_HMAC_NT:					type = L"rc4_hmac_nt      "; break;
	case KERB_ETYPE_RC4_HMAC_NT_EXP:				type = L"rc4_hmac_nt_exp  "; break;
	case KERB_ETYPE_RC4_PLAIN_OLD:					type = L"rc4_plain_old    "; break;
	case KERB_ETYPE_RC4_PLAIN_OLD_EXP:				type = L"rc4_plain_old_exp"; break;
	case KERB_ETYPE_RC4_HMAC_OLD:					type = L"rc4_hmac_old     "; break;
	case KERB_ETYPE_RC4_HMAC_OLD_EXP:				type = L"rc4_hmac_old_exp "; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96_PLAIN:	type = L"aes128_hmac_plain"; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96_PLAIN:	type = L"aes256_hmac_plain"; break;
	case KERB_ETYPE_AES128_CTS_HMAC_SHA1_96:		type = L"aes128_hmac      "; break;
	case KERB_ETYPE_AES256_CTS_HMAC_SHA1_96:		type = L"aes256_hmac      "; break;
	default:										type = L"unknow           "; break;
	}
	return type;
}