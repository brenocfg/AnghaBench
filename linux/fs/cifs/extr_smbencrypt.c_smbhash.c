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
struct des_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  DES_KEY_SIZE ; 
 int ENOENT ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  des_encrypt (struct des_ctx*,unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  des_expand_key (struct des_ctx*,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  memzero_explicit (struct des_ctx*,int) ; 
 int /*<<< orphan*/  str_to_key (unsigned char*,unsigned char*) ; 

__attribute__((used)) static int
smbhash(unsigned char *out, const unsigned char *in, unsigned char *key)
{
	unsigned char key2[8];
	struct des_ctx ctx;

	str_to_key(key, key2);

	if (fips_enabled) {
		cifs_dbg(VFS, "FIPS compliance enabled: DES not permitted\n");
		return -ENOENT;
	}

	des_expand_key(&ctx, key2, DES_KEY_SIZE);
	des_encrypt(&ctx, out, in);
	memzero_explicit(&ctx, sizeof(ctx));

	return 0;
}