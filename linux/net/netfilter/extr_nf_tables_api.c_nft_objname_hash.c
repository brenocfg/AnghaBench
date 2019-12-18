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
typedef  int /*<<< orphan*/  u32 ;
struct nft_object_hash_key {int /*<<< orphan*/  name; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nft_objname_hash(const void *data, u32 len, u32 seed)
{
	const struct nft_object_hash_key *k = data;

	seed ^= hash_ptr(k->table, 32);

	return jhash(k->name, strlen(k->name), seed);
}