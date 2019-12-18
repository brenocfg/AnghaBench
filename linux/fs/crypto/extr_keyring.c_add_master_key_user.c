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
struct key {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  identifier; } ;
struct TYPE_4__ {TYPE_1__ u; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_users; TYPE_2__ mk_spec; } ;

/* Variables and functions */
 int FSCRYPT_MK_USER_DESCRIPTION_SIZE ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int KEY_POS_SEARCH ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_gid () ; 
 int /*<<< orphan*/  format_mk_user_description (char*,int /*<<< orphan*/ ) ; 
 struct key* key_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int key_instantiate_and_link (struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_fscrypt_user ; 

__attribute__((used)) static int add_master_key_user(struct fscrypt_master_key *mk)
{
	char description[FSCRYPT_MK_USER_DESCRIPTION_SIZE];
	struct key *mk_user;
	int err;

	format_mk_user_description(description, mk->mk_spec.u.identifier);
	mk_user = key_alloc(&key_type_fscrypt_user, description,
			    current_fsuid(), current_gid(), current_cred(),
			    KEY_POS_SEARCH | KEY_USR_VIEW, 0, NULL);
	if (IS_ERR(mk_user))
		return PTR_ERR(mk_user);

	err = key_instantiate_and_link(mk_user, NULL, 0, mk->mk_users, NULL);
	key_put(mk_user);
	return err;
}