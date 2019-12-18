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
struct aa_loaddata {scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 scalar_t__ aa_g_hash_policy ; 
 scalar_t__ aa_hash_size () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool aa_rawdata_eq(struct aa_loaddata *l, struct aa_loaddata *r)
{
	if (l->size != r->size)
		return false;
	if (aa_g_hash_policy && memcmp(l->hash, r->hash, aa_hash_size()) != 0)
		return false;
	return memcmp(l->data, r->data, r->size) == 0;
}