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
struct key {int dummy; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_users; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 struct key* find_master_key_user (struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int key_unlink (int /*<<< orphan*/ ,struct key*) ; 

__attribute__((used)) static int remove_master_key_user(struct fscrypt_master_key *mk)
{
	struct key *mk_user;
	int err;

	mk_user = find_master_key_user(mk);
	if (IS_ERR(mk_user))
		return PTR_ERR(mk_user);
	err = key_unlink(mk->mk_users, mk_user);
	key_put(mk_user);
	return err;
}