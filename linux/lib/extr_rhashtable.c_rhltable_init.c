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
struct TYPE_2__ {int rhlist; } ;
struct rhltable {TYPE_1__ ht; } ;
struct rhashtable_params {int dummy; } ;

/* Variables and functions */
 int rhashtable_init (TYPE_1__*,struct rhashtable_params const*) ; 

int rhltable_init(struct rhltable *hlt, const struct rhashtable_params *params)
{
	int err;

	err = rhashtable_init(&hlt->ht, params);
	hlt->ht.rhlist = true;
	return err;
}