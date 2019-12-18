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
typedef  int /*<<< orphan*/  u32 ;
struct ecryptfs_mount_crypt_stat {int /*<<< orphan*/  global_auth_tok_list_mutex; int /*<<< orphan*/  global_auth_tok_list; } ;
struct ecryptfs_global_auth_tok {char* sig; int /*<<< orphan*/  mount_crypt_stat_list; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t ECRYPTFS_SIG_SIZE_HEX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ecryptfs_global_auth_tok_cache ; 
 struct ecryptfs_global_auth_tok* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
ecryptfs_add_global_auth_tok(struct ecryptfs_mount_crypt_stat *mount_crypt_stat,
			     char *sig, u32 global_auth_tok_flags)
{
	struct ecryptfs_global_auth_tok *new_auth_tok;

	new_auth_tok = kmem_cache_zalloc(ecryptfs_global_auth_tok_cache,
					GFP_KERNEL);
	if (!new_auth_tok)
		return -ENOMEM;

	memcpy(new_auth_tok->sig, sig, ECRYPTFS_SIG_SIZE_HEX);
	new_auth_tok->flags = global_auth_tok_flags;
	new_auth_tok->sig[ECRYPTFS_SIG_SIZE_HEX] = '\0';
	mutex_lock(&mount_crypt_stat->global_auth_tok_list_mutex);
	list_add(&new_auth_tok->mount_crypt_stat_list,
		 &mount_crypt_stat->global_auth_tok_list);
	mutex_unlock(&mount_crypt_stat->global_auth_tok_list_mutex);
	return 0;
}