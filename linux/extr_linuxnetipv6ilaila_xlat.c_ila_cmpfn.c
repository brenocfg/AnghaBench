#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rhashtable_compare_arg {scalar_t__ key; } ;
struct TYPE_4__ {scalar_t__ v64; } ;
struct TYPE_5__ {TYPE_1__ locator_match; } ;
struct TYPE_6__ {TYPE_2__ ip; } ;
struct ila_map {TYPE_3__ xp; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */

__attribute__((used)) static int ila_cmpfn(struct rhashtable_compare_arg *arg,
		     const void *obj)
{
	const struct ila_map *ila = obj;

	return (ila->xp.ip.locator_match.v64 != *(__be64 *)arg->key);
}