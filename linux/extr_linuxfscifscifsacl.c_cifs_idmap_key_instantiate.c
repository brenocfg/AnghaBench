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
struct key_preparsed_payload {int datalen; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {char** data; } ;
struct key {int datalen; TYPE_1__ payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cifs_idmap_key_instantiate(struct key *key, struct key_preparsed_payload *prep)
{
	char *payload;

	/*
	 * If the payload is less than or equal to the size of a pointer, then
	 * an allocation here is wasteful. Just copy the data directly to the
	 * payload.value union member instead.
	 *
	 * With this however, you must check the datalen before trying to
	 * dereference payload.data!
	 */
	if (prep->datalen <= sizeof(key->payload)) {
		key->payload.data[0] = NULL;
		memcpy(&key->payload, prep->data, prep->datalen);
	} else {
		payload = kmemdup(prep->data, prep->datalen, GFP_KERNEL);
		if (!payload)
			return -ENOMEM;
		key->payload.data[0] = payload;
	}

	key->datalen = prep->datalen;
	return 0;
}