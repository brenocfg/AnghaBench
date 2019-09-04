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
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_3__ {int /*<<< orphan*/  (* hash_final ) (unsigned char*,void*) ;int /*<<< orphan*/  (* hash_update ) (void*,unsigned char const*,int /*<<< orphan*/  const) ;int /*<<< orphan*/  const block_size; int /*<<< orphan*/  (* hash_init ) (void*) ;} ;
typedef  TYPE_1__ php_hash_ops ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned char const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub3 (void*,unsigned char const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub4 (unsigned char*,void*) ; 

__attribute__((used)) static inline void php_hash_hmac_round(unsigned char *final, const php_hash_ops *ops, void *context, const unsigned char *key, const unsigned char *data, const zend_long data_size) {
	ops->hash_init(context);
	ops->hash_update(context, key, ops->block_size);
	ops->hash_update(context, data, data_size);
	ops->hash_final(final, context);
}