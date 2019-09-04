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
struct user_key_payload {size_t datalen; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {struct user_key_payload** data; } ;
struct key_preparsed_payload {size_t datalen; size_t quotalen; int /*<<< orphan*/  data; TYPE_1__ payload; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct user_key_payload* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int user_preparse(struct key_preparsed_payload *prep)
{
	struct user_key_payload *upayload;
	size_t datalen = prep->datalen;

	if (datalen <= 0 || datalen > 32767 || !prep->data)
		return -EINVAL;

	upayload = kmalloc(sizeof(*upayload) + datalen, GFP_KERNEL);
	if (!upayload)
		return -ENOMEM;

	/* attach the data */
	prep->quotalen = datalen;
	prep->payload.data[0] = upayload;
	upayload->datalen = datalen;
	memcpy(upayload->data, prep->data, datalen);
	return 0;
}