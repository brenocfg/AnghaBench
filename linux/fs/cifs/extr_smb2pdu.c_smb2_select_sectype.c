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
struct TCP_Server_Info {int /*<<< orphan*/  sec_mskerberos; int /*<<< orphan*/  sec_kerberos; int /*<<< orphan*/  sec_ntlmssp; } ;
typedef  enum securityEnum { ____Placeholder_securityEnum } securityEnum ;

/* Variables and functions */
 int CIFSSEC_MAY_KRB5 ; 
 int CIFSSEC_MAY_NTLMSSP ; 
#define  Kerberos 131 
#define  NTLMv2 130 
#define  RawNTLMSSP 129 
#define  Unspecified 128 
 int global_secflags ; 

enum securityEnum
smb2_select_sectype(struct TCP_Server_Info *server, enum securityEnum requested)
{
	switch (requested) {
	case Kerberos:
	case RawNTLMSSP:
		return requested;
	case NTLMv2:
		return RawNTLMSSP;
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
}