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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cluster_dist_free_ht ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HashTable *cluster_dist_create() {
    HashTable *ret;

    ALLOC_HASHTABLE(ret);
    zend_hash_init(ret, 0, NULL, cluster_dist_free_ht, 0);

    return ret;
}