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
 int /*<<< orphan*/  CLUSTER_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 double INT_MAX ; 
 int SUCCESS ; 
 scalar_t__ zend_hash_num_elements (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cluster_validate_args(double timeout, double read_timeout, HashTable *seeds) {
    if (timeout < 0L || timeout > INT_MAX) {
        CLUSTER_THROW_EXCEPTION("Invalid timeout", 0);
        return FAILURE;
    }
    if (read_timeout < 0L || read_timeout > INT_MAX) {
        CLUSTER_THROW_EXCEPTION("Invalid read timeout", 0);
        return FAILURE;
    }
    /* Make sure there are some seeds */
    if (zend_hash_num_elements(seeds) == 0) {
        CLUSTER_THROW_EXCEPTION("Must pass seeds", 0);
        return FAILURE;
    }

    return SUCCESS;
}