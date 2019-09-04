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
struct key_preparsed_payload {int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {char** data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_spnego_key_instantiate(struct key *key, struct key_preparsed_payload *prep)
{
	char *payload;
	int ret;

	ret = -ENOMEM;
	payload = kmemdup(prep->data, prep->datalen, GFP_KERNEL);
	if (!payload)
		goto error;

	/* attach the data */
	key->payload.data[0] = payload;
	ret = 0;

error:
	return ret;
}