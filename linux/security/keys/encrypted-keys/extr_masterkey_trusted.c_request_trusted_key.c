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
typedef  int /*<<< orphan*/  u8 ;
struct trusted_key_payload {size_t key_len; int /*<<< orphan*/ * key; } ;
struct TYPE_2__ {struct trusted_key_payload** data; } ;
struct key {TYPE_1__ payload; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_type_trusted ; 
 struct key* request_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

struct key *request_trusted_key(const char *trusted_desc,
				const u8 **master_key, size_t *master_keylen)
{
	struct trusted_key_payload *tpayload;
	struct key *tkey;

	tkey = request_key(&key_type_trusted, trusted_desc, NULL);
	if (IS_ERR(tkey))
		goto error;

	down_read(&tkey->sem);
	tpayload = tkey->payload.data[0];
	*master_key = tpayload->key;
	*master_keylen = tpayload->key_len;
error:
	return tkey;
}