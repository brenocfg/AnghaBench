#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_persistent_script ;
typedef  int /*<<< orphan*/  zend_file_cache_metainfo ;
typedef  int /*<<< orphan*/  (* serialize_callback_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;
struct TYPE_9__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
struct TYPE_8__ {int nNumUsed; TYPE_2__* arData; } ;
typedef  TYPE_1__ HashTable ;
typedef  TYPE_2__ Bucket ;

/* Variables and functions */
 int HASH_FLAG_UNINITIALIZED ; 
 int HT_FLAGS (TYPE_1__*) ; 
 scalar_t__ IS_SERIALIZED (TYPE_2__*) ; 
 scalar_t__ IS_UNDEF ; 
 int /*<<< orphan*/  SERIALIZE_PTR (TYPE_2__*) ; 
 int /*<<< orphan*/  SERIALIZE_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_2__*) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_file_cache_serialize_hash(HashTable                *ht,
                                           zend_persistent_script   *script,
                                           zend_file_cache_metainfo *info,
                                           void                     *buf,
                                           serialize_callback_t      func)
{
	Bucket *p, *end;

	if (HT_FLAGS(ht) & HASH_FLAG_UNINITIALIZED) {
		ht->arData = NULL;
		return;
	}
	if (IS_SERIALIZED(ht->arData)) {
		return;
	}
	SERIALIZE_PTR(ht->arData);
	p = ht->arData;
	UNSERIALIZE_PTR(p);
	end = p + ht->nNumUsed;
	while (p < end) {
		if (Z_TYPE(p->val) != IS_UNDEF) {
			SERIALIZE_STR(p->key);
			func(&p->val, script, info, buf);
		}
		p++;
	}
}