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
typedef  int /*<<< orphan*/  substring_t ;
struct smb_vol {int sign; int nullauth; int /*<<< orphan*/  sectype; } ;

/* Variables and functions */
 int /*<<< orphan*/  Kerberos ; 
 int /*<<< orphan*/  LANMAN ; 
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  NTLM ; 
 int /*<<< orphan*/  NTLMv2 ; 
#define  Opt_ntlm 138 
#define  Opt_sec_krb5 137 
#define  Opt_sec_krb5i 136 
#define  Opt_sec_krb5p 135 
#define  Opt_sec_lanman 134 
#define  Opt_sec_none 133 
#define  Opt_sec_ntlmi 132 
#define  Opt_sec_ntlmssp 131 
#define  Opt_sec_ntlmsspi 130 
#define  Opt_sec_ntlmv2 129 
#define  Opt_sec_ntlmv2i 128 
 int /*<<< orphan*/  RawNTLMSSP ; 
 int /*<<< orphan*/  Unspecified ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_secflavor_tokens ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cifs_parse_security_flavors(char *value,
				       struct smb_vol *vol)
{

	substring_t args[MAX_OPT_ARGS];

	/*
	 * With mount options, the last one should win. Reset any existing
	 * settings back to default.
	 */
	vol->sectype = Unspecified;
	vol->sign = false;

	switch (match_token(value, cifs_secflavor_tokens, args)) {
	case Opt_sec_krb5p:
		cifs_dbg(VFS, "sec=krb5p is not supported!\n");
		return 1;
	case Opt_sec_krb5i:
		vol->sign = true;
		/* Fallthrough */
	case Opt_sec_krb5:
		vol->sectype = Kerberos;
		break;
	case Opt_sec_ntlmsspi:
		vol->sign = true;
		/* Fallthrough */
	case Opt_sec_ntlmssp:
		vol->sectype = RawNTLMSSP;
		break;
	case Opt_sec_ntlmi:
		vol->sign = true;
		/* Fallthrough */
	case Opt_ntlm:
		vol->sectype = NTLM;
		break;
	case Opt_sec_ntlmv2i:
		vol->sign = true;
		/* Fallthrough */
	case Opt_sec_ntlmv2:
		vol->sectype = NTLMv2;
		break;
#ifdef CONFIG_CIFS_WEAK_PW_HASH
	case Opt_sec_lanman:
		vol->sectype = LANMAN;
		break;
#endif
	case Opt_sec_none:
		vol->nullauth = 1;
		break;
	default:
		cifs_dbg(VFS, "bad security option: %s\n", value);
		return 1;
	}

	return 0;
}