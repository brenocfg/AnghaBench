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
struct keyring_read_iterator_context {scalar_t__ count; scalar_t__ buflen; int /*<<< orphan*/  buffer; } ;
struct key {int /*<<< orphan*/  serial; TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct key* keyring_ptr_to_key (void const*) ; 
 int put_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keyring_read_iterator(const void *object, void *data)
{
	struct keyring_read_iterator_context *ctx = data;
	const struct key *key = keyring_ptr_to_key(object);
	int ret;

	kenter("{%s,%d},,{%zu/%zu}",
	       key->type->name, key->serial, ctx->count, ctx->buflen);

	if (ctx->count >= ctx->buflen)
		return 1;

	ret = put_user(key->serial, ctx->buffer);
	if (ret < 0)
		return ret;
	ctx->buffer++;
	ctx->count += sizeof(key->serial);
	return 0;
}