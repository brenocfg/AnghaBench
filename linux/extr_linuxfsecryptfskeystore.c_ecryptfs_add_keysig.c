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
struct ecryptfs_key_sig {char* keysig; int /*<<< orphan*/  crypt_stat_list; } ;
struct ecryptfs_crypt_stat {int /*<<< orphan*/  keysig_list; } ;

/* Variables and functions */
 size_t ECRYPTFS_SIG_SIZE_HEX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ecryptfs_key_sig_cache ; 
 struct ecryptfs_key_sig* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

int ecryptfs_add_keysig(struct ecryptfs_crypt_stat *crypt_stat, char *sig)
{
	struct ecryptfs_key_sig *new_key_sig;

	new_key_sig = kmem_cache_alloc(ecryptfs_key_sig_cache, GFP_KERNEL);
	if (!new_key_sig)
		return -ENOMEM;

	memcpy(new_key_sig->keysig, sig, ECRYPTFS_SIG_SIZE_HEX);
	new_key_sig->keysig[ECRYPTFS_SIG_SIZE_HEX] = '\0';
	/* Caller must hold keysig_list_mutex */
	list_add(&new_key_sig->crypt_stat_list, &crypt_stat->keysig_list);

	return 0;
}