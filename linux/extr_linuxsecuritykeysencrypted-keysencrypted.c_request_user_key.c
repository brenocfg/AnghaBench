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
typedef  int /*<<< orphan*/  u8 ;
struct user_key_payload {size_t datalen; int /*<<< orphan*/ * data; } ;
struct key {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  EKEYREVOKED ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_user ; 
 struct key* request_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

__attribute__((used)) static struct key *request_user_key(const char *master_desc, const u8 **master_key,
				    size_t *master_keylen)
{
	const struct user_key_payload *upayload;
	struct key *ukey;

	ukey = request_key(&key_type_user, master_desc, NULL);
	if (IS_ERR(ukey))
		goto error;

	down_read(&ukey->sem);
	upayload = user_key_payload_locked(ukey);
	if (!upayload) {
		/* key was revoked before we acquired its semaphore */
		up_read(&ukey->sem);
		key_put(ukey);
		ukey = ERR_PTR(-EKEYREVOKED);
		goto error;
	}
	*master_key = upayload->data;
	*master_keylen = upayload->datalen;
error:
	return ukey;
}