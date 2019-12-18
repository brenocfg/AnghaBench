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
struct fscrypt_master_key_secret {int /*<<< orphan*/  hkdf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscrypt_destroy_hkdf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memzero_explicit (struct fscrypt_master_key_secret*,int) ; 

__attribute__((used)) static void wipe_master_key_secret(struct fscrypt_master_key_secret *secret)
{
	fscrypt_destroy_hkdf(&secret->hkdf);
	memzero_explicit(secret, sizeof(*secret));
}