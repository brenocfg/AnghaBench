#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dn_zone {int dz_order; } ;
struct TYPE_3__ {int /*<<< orphan*/  datum; } ;
typedef  TYPE_1__ dn_fib_key_t ;
typedef  int /*<<< orphan*/  dn_fib_idx_t ;

/* Variables and functions */
 int DZ_HASHMASK (struct dn_zone*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dn_fib_idx_t dn_hash(dn_fib_key_t key, struct dn_zone *dz)
{
	u16 h = le16_to_cpu(key.datum)>>(16 - dz->dz_order);
	h ^= (h >> 10);
	h ^= (h >> 6);
	h &= DZ_HASHMASK(dz);
	return *(dn_fib_idx_t *)&h;
}