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
struct sess_data {int /*<<< orphan*/  func; } ;
struct cifs_ses {int /*<<< orphan*/  sectype; int /*<<< orphan*/  server; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FYI ; 
#define  Kerberos 132 
#define  LANMAN 131 
#define  NTLM 130 
#define  NTLMv2 129 
#define  RawNTLMSSP 128 
 int Unspecified ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int cifs_select_sectype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sess_auth_kerberos ; 
 int /*<<< orphan*/  sess_auth_lanman ; 
 int /*<<< orphan*/  sess_auth_ntlm ; 
 int /*<<< orphan*/  sess_auth_ntlmv2 ; 
 int /*<<< orphan*/  sess_auth_rawntlmssp_negotiate ; 

__attribute__((used)) static int select_sec(struct cifs_ses *ses, struct sess_data *sess_data)
{
	int type;

	type = cifs_select_sectype(ses->server, ses->sectype);
	cifs_dbg(FYI, "sess setup type %d\n", type);
	if (type == Unspecified) {
		cifs_dbg(VFS,
			"Unable to select appropriate authentication method!");
		return -EINVAL;
	}

	switch (type) {
	case LANMAN:
		/* LANMAN and plaintext are less secure and off by default.
		 * So we make this explicitly be turned on in kconfig (in the
		 * build) and turned on at runtime (changed from the default)
		 * in proc/fs/cifs or via mount parm.  Unfortunately this is
		 * needed for old Win (e.g. Win95), some obscure NAS and OS/2 */
#ifdef CONFIG_CIFS_WEAK_PW_HASH
		sess_data->func = sess_auth_lanman;
		break;
#else
		return -EOPNOTSUPP;
#endif
	case NTLM:
		sess_data->func = sess_auth_ntlm;
		break;
	case NTLMv2:
		sess_data->func = sess_auth_ntlmv2;
		break;
	case Kerberos:
#ifdef CONFIG_CIFS_UPCALL
		sess_data->func = sess_auth_kerberos;
		break;
#else
		cifs_dbg(VFS, "Kerberos negotiated but upcall support disabled!\n");
		return -ENOSYS;
		break;
#endif /* CONFIG_CIFS_UPCALL */
	case RawNTLMSSP:
		sess_data->func = sess_auth_rawntlmssp_negotiate;
		break;
	default:
		cifs_dbg(VFS, "secType %d not supported!\n", type);
		return -ENOSYS;
	}

	return 0;
}