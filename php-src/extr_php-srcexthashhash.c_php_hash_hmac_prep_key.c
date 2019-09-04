#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t const block_size; int /*<<< orphan*/  (* hash_final ) (unsigned char*,void*) ;int /*<<< orphan*/  (* hash_update ) (void*,unsigned char const*,size_t const) ;int /*<<< orphan*/  (* hash_init ) (void*) ;} ;
typedef  TYPE_1__ php_hash_ops ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t const) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  php_hash_string_xor_char (unsigned char*,unsigned char*,int,size_t const) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned char const*,size_t const) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,void*) ; 

__attribute__((used)) static inline void php_hash_hmac_prep_key(unsigned char *K, const php_hash_ops *ops, void *context, const unsigned char *key, const size_t key_len) {
	memset(K, 0, ops->block_size);
	if (key_len > ops->block_size) {
		/* Reduce the key first */
		ops->hash_init(context);
		ops->hash_update(context, key, key_len);
		ops->hash_final(K, context);
	} else {
		memcpy(K, key, key_len);
	}
	/* XOR the key with 0x36 to get the ipad) */
	php_hash_string_xor_char(K, K, 0x36, ops->block_size);
}