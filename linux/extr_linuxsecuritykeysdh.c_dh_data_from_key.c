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
typedef  int /*<<< orphan*/  uint8_t ;
struct user_key_payload {int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/ * type; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  key_serial_t ;
typedef  int /*<<< orphan*/  key_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_NEED_READ ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_type_user ; 
 long key_validate (struct key*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_user_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

__attribute__((used)) static ssize_t dh_data_from_key(key_serial_t keyid, void **data)
{
	struct key *key;
	key_ref_t key_ref;
	long status;
	ssize_t ret;

	key_ref = lookup_user_key(keyid, 0, KEY_NEED_READ);
	if (IS_ERR(key_ref)) {
		ret = -ENOKEY;
		goto error;
	}

	key = key_ref_to_ptr(key_ref);

	ret = -EOPNOTSUPP;
	if (key->type == &key_type_user) {
		down_read(&key->sem);
		status = key_validate(key);
		if (status == 0) {
			const struct user_key_payload *payload;
			uint8_t *duplicate;

			payload = user_key_payload_locked(key);

			duplicate = kmemdup(payload->data, payload->datalen,
					    GFP_KERNEL);
			if (duplicate) {
				*data = duplicate;
				ret = payload->datalen;
			} else {
				ret = -ENOMEM;
			}
		}
		up_read(&key->sem);
	}

	key_put(key);
error:
	return ret;
}