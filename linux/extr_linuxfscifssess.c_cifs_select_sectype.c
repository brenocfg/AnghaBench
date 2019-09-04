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
struct TCP_Server_Info {int negflavor; int /*<<< orphan*/  sec_mskerberos; int /*<<< orphan*/  sec_kerberos; int /*<<< orphan*/  sec_ntlmssp; } ;
typedef  enum securityEnum { ____Placeholder_securityEnum } securityEnum ;

/* Variables and functions */
 int CIFSSEC_MAY_KRB5 ; 
 int CIFSSEC_MAY_LANMAN ; 
 int CIFSSEC_MAY_NTLM ; 
 int CIFSSEC_MAY_NTLMSSP ; 
 int CIFSSEC_MAY_NTLMV2 ; 
#define  CIFS_NEGFLAVOR_EXTENDED 136 
#define  CIFS_NEGFLAVOR_LANMAN 135 
#define  CIFS_NEGFLAVOR_UNENCAP 134 
#define  Kerberos 133 
#define  LANMAN 132 
#define  NTLM 131 
#define  NTLMv2 130 
#define  RawNTLMSSP 129 
#define  Unspecified 128 
 int global_secflags ; 

enum securityEnum
cifs_select_sectype(struct TCP_Server_Info *server, enum securityEnum requested)
{
	switch (server->negflavor) {
	case CIFS_NEGFLAVOR_EXTENDED:
		switch (requested) {
		case Kerberos:
		case RawNTLMSSP:
			return requested;
		case Unspecified:
			if (server->sec_ntlmssp &&
			    (global_secflags & CIFSSEC_MAY_NTLMSSP))
				return RawNTLMSSP;
			if ((server->sec_kerberos || server->sec_mskerberos) &&
			    (global_secflags & CIFSSEC_MAY_KRB5))
				return Kerberos;
			/* Fallthrough */
		default:
			return Unspecified;
		}
	case CIFS_NEGFLAVOR_UNENCAP:
		switch (requested) {
		case NTLM:
		case NTLMv2:
			return requested;
		case Unspecified:
			if (global_secflags & CIFSSEC_MAY_NTLMV2)
				return NTLMv2;
			if (global_secflags & CIFSSEC_MAY_NTLM)
				return NTLM;
		default:
			/* Fallthrough to attempt LANMAN authentication next */
			break;
		}
	case CIFS_NEGFLAVOR_LANMAN:
		switch (requested) {
		case LANMAN:
			return requested;
		case Unspecified:
			if (global_secflags & CIFSSEC_MAY_LANMAN)
				return LANMAN;
			/* Fallthrough */
		default:
			return Unspecified;
		}
	default:
		return Unspecified;
	}
}