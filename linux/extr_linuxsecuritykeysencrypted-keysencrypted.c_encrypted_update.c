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
struct key_preparsed_payload {size_t datalen; char* data; } ;
struct TYPE_2__ {struct encrypted_key_payload** data; } ;
struct key {TYPE_1__ payload; } ;
struct encrypted_key_payload {char* iv; char* payload_data; size_t payload_datalen; int /*<<< orphan*/  rcu; int /*<<< orphan*/  datalen; int /*<<< orphan*/  format; int /*<<< orphan*/  master_desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOKEY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct encrypted_key_payload*) ; 
 int PTR_ERR (struct encrypted_key_payload*) ; 
 int /*<<< orphan*/  __ekey_init (struct encrypted_key_payload*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int datablob_parse (char*,char const**,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct encrypted_key_payload* encrypted_key_alloc (struct key*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encrypted_rcu_free ; 
 size_t ivsize ; 
 scalar_t__ key_is_negative (struct key*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  rcu_assign_keypointer (struct key*,struct encrypted_key_payload*) ; 
 int valid_master_desc (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int encrypted_update(struct key *key, struct key_preparsed_payload *prep)
{
	struct encrypted_key_payload *epayload = key->payload.data[0];
	struct encrypted_key_payload *new_epayload;
	char *buf;
	char *new_master_desc = NULL;
	const char *format = NULL;
	size_t datalen = prep->datalen;
	int ret = 0;

	if (key_is_negative(key))
		return -ENOKEY;
	if (datalen <= 0 || datalen > 32767 || !prep->data)
		return -EINVAL;

	buf = kmalloc(datalen + 1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[datalen] = 0;
	memcpy(buf, prep->data, datalen);
	ret = datablob_parse(buf, &format, &new_master_desc, NULL, NULL);
	if (ret < 0)
		goto out;

	ret = valid_master_desc(new_master_desc, epayload->master_desc);
	if (ret < 0)
		goto out;

	new_epayload = encrypted_key_alloc(key, epayload->format,
					   new_master_desc, epayload->datalen);
	if (IS_ERR(new_epayload)) {
		ret = PTR_ERR(new_epayload);
		goto out;
	}

	__ekey_init(new_epayload, epayload->format, new_master_desc,
		    epayload->datalen);

	memcpy(new_epayload->iv, epayload->iv, ivsize);
	memcpy(new_epayload->payload_data, epayload->payload_data,
	       epayload->payload_datalen);

	rcu_assign_keypointer(key, new_epayload);
	call_rcu(&epayload->rcu, encrypted_rcu_free);
out:
	kzfree(buf);
	return ret;
}