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
struct dn_zone {struct dn_fib_node** dz_hash; } ;
struct dn_fib_node {int dummy; } ;
typedef  int /*<<< orphan*/  dn_fib_key_t ;
struct TYPE_2__ {size_t datum; } ;

/* Variables and functions */
 TYPE_1__ dn_hash (int /*<<< orphan*/ ,struct dn_zone*) ; 

__attribute__((used)) static inline struct dn_fib_node *dz_chain(dn_fib_key_t key, struct dn_zone *dz)
{
	return dz->dz_hash[dn_hash(key, dz).datum];
}