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
union ubifs_key {int /*<<< orphan*/ * u32; } ;
struct ubifs_info {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */

__attribute__((used)) static inline ino_t key_inum(const struct ubifs_info *c, const void *k)
{
	const union ubifs_key *key = k;

	return key->u32[0];
}