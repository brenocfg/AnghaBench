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
struct fscache_cookie {scalar_t__ key_hash; scalar_t__ parent; int key_len; scalar_t__ type; void* key; int /*<<< orphan*/  inline_key; } ;

/* Variables and functions */
 long memcmp (void const*,void const*,int) ; 

__attribute__((used)) static long fscache_compare_cookie(const struct fscache_cookie *a,
				   const struct fscache_cookie *b)
{
	const void *ka, *kb;

	if (a->key_hash != b->key_hash)
		return (long)a->key_hash - (long)b->key_hash;
	if (a->parent != b->parent)
		return (long)a->parent - (long)b->parent;
	if (a->key_len != b->key_len)
		return (long)a->key_len - (long)b->key_len;
	if (a->type != b->type)
		return (long)a->type - (long)b->type;

	if (a->key_len <= sizeof(a->inline_key)) {
		ka = &a->inline_key;
		kb = &b->inline_key;
	} else {
		ka = a->key;
		kb = b->key;
	}
	return memcmp(ka, kb, a->key_len);
}