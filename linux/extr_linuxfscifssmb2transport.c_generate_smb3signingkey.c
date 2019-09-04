#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  context; int /*<<< orphan*/  label; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  label; } ;
struct TYPE_6__ {int /*<<< orphan*/  context; int /*<<< orphan*/  label; } ;
struct derivation_triplet {TYPE_2__ decryption; TYPE_1__ encryption; TYPE_3__ signing; } ;
struct cifs_ses {int /*<<< orphan*/  smb3decryptionkey; int /*<<< orphan*/  smb3encryptionkey; int /*<<< orphan*/  smb3signingkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB3_SIGN_KEY_SIZE ; 
 int generate_key (struct cifs_ses*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
generate_smb3signingkey(struct cifs_ses *ses,
			const struct derivation_triplet *ptriplet)
{
	int rc;

	rc = generate_key(ses, ptriplet->signing.label,
			  ptriplet->signing.context, ses->smb3signingkey,
			  SMB3_SIGN_KEY_SIZE);
	if (rc)
		return rc;

	rc = generate_key(ses, ptriplet->encryption.label,
			  ptriplet->encryption.context, ses->smb3encryptionkey,
			  SMB3_SIGN_KEY_SIZE);
	if (rc)
		return rc;

	rc = generate_key(ses, ptriplet->decryption.label,
			  ptriplet->decryption.context,
			  ses->smb3decryptionkey, SMB3_SIGN_KEY_SIZE);

	if (rc)
		return rc;

#ifdef CONFIG_CIFS_DEBUG_DUMP_KEYS
	cifs_dbg(VFS, "%s: dumping generated AES session keys\n", __func__);
	/*
	 * The session id is opaque in terms of endianness, so we can't
	 * print it as a long long. we dump it as we got it on the wire
	 */
	cifs_dbg(VFS, "Session Id    %*ph\n", (int)sizeof(ses->Suid),
			&ses->Suid);
	cifs_dbg(VFS, "Session Key   %*ph\n",
		 SMB2_NTLMV2_SESSKEY_SIZE, ses->auth_key.response);
	cifs_dbg(VFS, "Signing Key   %*ph\n",
		 SMB3_SIGN_KEY_SIZE, ses->smb3signingkey);
	cifs_dbg(VFS, "ServerIn Key  %*ph\n",
		 SMB3_SIGN_KEY_SIZE, ses->smb3encryptionkey);
	cifs_dbg(VFS, "ServerOut Key %*ph\n",
		 SMB3_SIGN_KEY_SIZE, ses->smb3decryptionkey);
#endif
	return rc;
}