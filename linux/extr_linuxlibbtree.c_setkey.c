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
struct btree_geo {int /*<<< orphan*/  keylen; } ;

/* Variables and functions */
 int /*<<< orphan*/  bkey (struct btree_geo*,unsigned long*,int) ; 
 int /*<<< orphan*/  longcpy (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setkey(struct btree_geo *geo, unsigned long *node, int n,
		   unsigned long *key)
{
	longcpy(bkey(geo, node, n), key, geo->keylen);
}