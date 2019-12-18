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
struct sadb_key {scalar_t__ sadb_key_len; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ sadb_key_len (struct sadb_key const*) ; 

__attribute__((used)) static int verify_key_len(const void *p)
{
	const struct sadb_key *key = p;

	if (sadb_key_len(key) > key->sadb_key_len)
		return -EINVAL;

	return 0;
}