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
struct key_type {int dummy; } ;
struct key {int dummy; } ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EKEYREVOKED ; 
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_CAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyring_search (int /*<<< orphan*/ ,struct key_type*,char const*,int) ; 
 int /*<<< orphan*/  make_key_ref (struct key*,int) ; 

__attribute__((used)) static struct key *search_fscrypt_keyring(struct key *keyring,
					  struct key_type *type,
					  const char *description)
{
	/*
	 * We need to mark the keyring reference as "possessed" so that we
	 * acquire permission to search it, via the KEY_POS_SEARCH permission.
	 */
	key_ref_t keyref = make_key_ref(keyring, true /* possessed */);

	keyref = keyring_search(keyref, type, description, false);
	if (IS_ERR(keyref)) {
		if (PTR_ERR(keyref) == -EAGAIN || /* not found */
		    PTR_ERR(keyref) == -EKEYREVOKED) /* recently invalidated */
			keyref = ERR_PTR(-ENOKEY);
		return ERR_CAST(keyref);
	}
	return key_ref_to_ptr(keyref);
}