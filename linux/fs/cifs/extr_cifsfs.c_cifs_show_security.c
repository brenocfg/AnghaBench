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
struct seq_file {int dummy; } ;
struct cifs_ses {int sectype; scalar_t__ sign; int /*<<< orphan*/  cred_uid; int /*<<< orphan*/ * user_name; } ;

/* Variables and functions */
#define  Kerberos 132 
#define  LANMAN 131 
#define  NTLM 130 
#define  NTLMv2 129 
#define  RawNTLMSSP 128 
 int Unspecified ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void
cifs_show_security(struct seq_file *s, struct cifs_ses *ses)
{
	if (ses->sectype == Unspecified) {
		if (ses->user_name == NULL)
			seq_puts(s, ",sec=none");
		return;
	}

	seq_puts(s, ",sec=");

	switch (ses->sectype) {
	case LANMAN:
		seq_puts(s, "lanman");
		break;
	case NTLMv2:
		seq_puts(s, "ntlmv2");
		break;
	case NTLM:
		seq_puts(s, "ntlm");
		break;
	case Kerberos:
		seq_printf(s, "krb5,cruid=%u", from_kuid_munged(&init_user_ns,ses->cred_uid));
		break;
	case RawNTLMSSP:
		seq_puts(s, "ntlmssp");
		break;
	default:
		/* shouldn't ever happen */
		seq_puts(s, "unknown");
		break;
	}

	if (ses->sign)
		seq_puts(s, "i");
}