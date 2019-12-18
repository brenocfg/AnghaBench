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
struct fscrypt_master_key_secret {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct fscrypt_master_key_secret*,struct fscrypt_master_key_secret*,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct fscrypt_master_key_secret*,int) ; 

__attribute__((used)) static void move_master_key_secret(struct fscrypt_master_key_secret *dst,
				   struct fscrypt_master_key_secret *src)
{
	memcpy(dst, src, sizeof(*dst));
	memzero_explicit(src, sizeof(*src));
}