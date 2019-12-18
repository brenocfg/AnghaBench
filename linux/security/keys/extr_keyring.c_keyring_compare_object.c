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
struct keyring_index_key {scalar_t__ type; scalar_t__ domain_tag; scalar_t__ desc_len; int /*<<< orphan*/  description; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ domain_tag; scalar_t__ desc_len; int /*<<< orphan*/  description; } ;
struct key {TYPE_1__ index_key; } ;

/* Variables and functions */
 struct key* keyring_ptr_to_key (void const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool keyring_compare_object(const void *object, const void *data)
{
	const struct keyring_index_key *index_key = data;
	const struct key *key = keyring_ptr_to_key(object);

	return key->index_key.type == index_key->type &&
		key->index_key.domain_tag == index_key->domain_tag &&
		key->index_key.desc_len == index_key->desc_len &&
		memcmp(key->index_key.description, index_key->description,
		       index_key->desc_len) == 0;
}