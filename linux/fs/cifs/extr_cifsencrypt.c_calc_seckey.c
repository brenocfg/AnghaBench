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
struct TYPE_3__ {int len; int /*<<< orphan*/  response; } ;
struct cifs_ses {TYPE_1__ auth_key; TYPE_2__* ntlmssp; } ;
struct arc4_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ciphertext; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CPHTXT_SIZE ; 
 int CIFS_SESS_KEY_SIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  arc4_crypt (struct arc4_ctx*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc4_setkey (struct arc4_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  get_random_bytes (unsigned char*,int) ; 
 struct arc4_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct arc4_ctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memzero_explicit (unsigned char*,int) ; 

int
calc_seckey(struct cifs_ses *ses)
{
	unsigned char sec_key[CIFS_SESS_KEY_SIZE]; /* a nonce */
	struct arc4_ctx *ctx_arc4;

	if (fips_enabled)
		return -ENODEV;

	get_random_bytes(sec_key, CIFS_SESS_KEY_SIZE);

	ctx_arc4 = kmalloc(sizeof(*ctx_arc4), GFP_KERNEL);
	if (!ctx_arc4) {
		cifs_dbg(VFS, "could not allocate arc4 context\n");
		return -ENOMEM;
	}

	arc4_setkey(ctx_arc4, ses->auth_key.response, CIFS_SESS_KEY_SIZE);
	arc4_crypt(ctx_arc4, ses->ntlmssp->ciphertext, sec_key,
		   CIFS_CPHTXT_SIZE);

	/* make secondary_key/nonce as session key */
	memcpy(ses->auth_key.response, sec_key, CIFS_SESS_KEY_SIZE);
	/* and make len as that of session key only */
	ses->auth_key.len = CIFS_SESS_KEY_SIZE;

	memzero_explicit(sec_key, CIFS_SESS_KEY_SIZE);
	kzfree(ctx_arc4);
	return 0;
}