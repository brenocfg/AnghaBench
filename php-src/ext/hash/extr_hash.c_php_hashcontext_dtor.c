#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {unsigned char* context; unsigned char* key; TYPE_1__* ops; } ;
typedef  TYPE_2__ php_hashcontext_object ;
struct TYPE_4__ {int /*<<< orphan*/  block_size; int /*<<< orphan*/  (* hash_final ) (unsigned char*,unsigned char*) ;int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_SECURE_ZERO (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (unsigned char*) ; 
 unsigned char* emalloc (int /*<<< orphan*/ ) ; 
 TYPE_2__* php_hashcontext_from_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char*) ; 

__attribute__((used)) static void php_hashcontext_dtor(zend_object *obj) {
	php_hashcontext_object *hash = php_hashcontext_from_object(obj);

	/* Just in case the algo has internally allocated resources */
	if (hash->context) {
		unsigned char *dummy = emalloc(hash->ops->digest_size);
		hash->ops->hash_final(dummy, hash->context);
		efree(dummy);
		efree(hash->context);
		hash->context = NULL;
	}

	if (hash->key) {
		ZEND_SECURE_ZERO(hash->key, hash->ops->block_size);
		efree(hash->key);
		hash->key = NULL;
	}
}