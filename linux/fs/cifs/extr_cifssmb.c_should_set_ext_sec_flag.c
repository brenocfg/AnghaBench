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
typedef  enum securityEnum { ____Placeholder_securityEnum } securityEnum ;

/* Variables and functions */
 int CIFSSEC_MAY_KRB5 ; 
 int CIFSSEC_MAY_NTLMSSP ; 
#define  Kerberos 130 
#define  RawNTLMSSP 129 
#define  Unspecified 128 
 int global_secflags ; 

__attribute__((used)) static bool
should_set_ext_sec_flag(enum securityEnum sectype)
{
	switch (sectype) {
	case RawNTLMSSP:
	case Kerberos:
		return true;
	case Unspecified:
		if (global_secflags &
		    (CIFSSEC_MAY_KRB5 | CIFSSEC_MAY_NTLMSSP))
			return true;
		/* Fallthrough */
	default:
		return false;
	}
}