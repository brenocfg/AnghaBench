#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct napi_struct {scalar_t__ gro_bitmask; TYPE_1__* gro_hash; } ;
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int GRO_HASH_BUCKETS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_gro_hash(struct napi_struct *napi)
{
	int i;

	for (i = 0; i < GRO_HASH_BUCKETS; i++) {
		INIT_LIST_HEAD(&napi->gro_hash[i].list);
		napi->gro_hash[i].count = 0;
	}
	napi->gro_bitmask = 0;
}