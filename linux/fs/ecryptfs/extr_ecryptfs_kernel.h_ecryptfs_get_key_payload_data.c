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
struct user_key_payload {scalar_t__ data; } ;
struct key {int dummy; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EKEYREVOKED ; 
 struct ecryptfs_auth_tok* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct ecryptfs_auth_tok* ecryptfs_get_encrypted_key_payload_data (struct key*) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

__attribute__((used)) static inline struct ecryptfs_auth_tok *
ecryptfs_get_key_payload_data(struct key *key)
{
	struct ecryptfs_auth_tok *auth_tok;
	struct user_key_payload *ukp;

	auth_tok = ecryptfs_get_encrypted_key_payload_data(key);
	if (auth_tok)
		return auth_tok;

	ukp = user_key_payload_locked(key);
	if (!ukp)
		return ERR_PTR(-EKEYREVOKED);

	return (struct ecryptfs_auth_tok *)ukp->data;
}