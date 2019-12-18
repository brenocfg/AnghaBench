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
typedef  int /*<<< orphan*/  uint64_t ;
struct sadb_key {int sadb_key_bits; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static inline int sadb_key_len(const struct sadb_key *key)
{
	int key_bytes = DIV_ROUND_UP(key->sadb_key_bits, 8);

	return DIV_ROUND_UP(sizeof(struct sadb_key) + key_bytes,
			    sizeof(uint64_t));
}