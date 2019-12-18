#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key_preparsed_payload {int dummy; } ;
struct key {int /*<<< orphan*/  sem; TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  key_ref_t ;
struct TYPE_2__ {int (* update ) (struct key*,struct key_preparsed_payload*) ;} ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int /*<<< orphan*/  KEY_NEED_WRITE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int key_permission (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_key_instantiated (struct key*,int /*<<< orphan*/ ) ; 
 int stub1 (struct key*,struct key_preparsed_payload*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline key_ref_t __key_update(key_ref_t key_ref,
				     struct key_preparsed_payload *prep)
{
	struct key *key = key_ref_to_ptr(key_ref);
	int ret;

	/* need write permission on the key to update it */
	ret = key_permission(key_ref, KEY_NEED_WRITE);
	if (ret < 0)
		goto error;

	ret = -EEXIST;
	if (!key->type->update)
		goto error;

	down_write(&key->sem);

	ret = key->type->update(key, prep);
	if (ret == 0)
		/* Updating a negative key positively instantiates it */
		mark_key_instantiated(key, 0);

	up_write(&key->sem);

	if (ret < 0)
		goto error;
out:
	return key_ref;

error:
	key_put(key);
	key_ref = ERR_PTR(ret);
	goto out;
}