#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_3__ {char* iov_base; int iov_len; } ;
struct derivation {TYPE_2__ context; TYPE_1__ label; } ;
struct derivation_triplet {struct derivation decryption; struct derivation encryption; struct derivation signing; } ;
struct cifs_ses {int /*<<< orphan*/  preauth_sha_hash; } ;

/* Variables and functions */
 int generate_smb3signingkey (struct cifs_ses*,struct derivation_triplet*) ; 

int
generate_smb311signingkey(struct cifs_ses *ses)

{
	struct derivation_triplet triplet;
	struct derivation *d;

	d = &triplet.signing;
	d->label.iov_base = "SMBSigningKey";
	d->label.iov_len = 14;
	d->context.iov_base = ses->preauth_sha_hash;
	d->context.iov_len = 64;

	d = &triplet.encryption;
	d->label.iov_base = "SMBC2SCipherKey";
	d->label.iov_len = 16;
	d->context.iov_base = ses->preauth_sha_hash;
	d->context.iov_len = 64;

	d = &triplet.decryption;
	d->label.iov_base = "SMBS2CCipherKey";
	d->label.iov_len = 16;
	d->context.iov_base = ses->preauth_sha_hash;
	d->context.iov_len = 64;

	return generate_smb3signingkey(ses, &triplet);
}