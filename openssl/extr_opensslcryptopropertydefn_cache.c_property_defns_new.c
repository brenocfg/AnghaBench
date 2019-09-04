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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 void* lh_PROPERTY_DEFN_ELEM_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_defn_cmp ; 
 int /*<<< orphan*/  property_defn_hash ; 

__attribute__((used)) static void *property_defns_new(OPENSSL_CTX *ctx) {
    return lh_PROPERTY_DEFN_ELEM_new(&property_defn_hash, &property_defn_cmp);
}