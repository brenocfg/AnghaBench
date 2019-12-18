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
struct ubifs_info {int dummy; } ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 struct shash_desc* __ubifs_hash_get_desc (struct ubifs_info const*) ; 
 scalar_t__ ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static inline struct shash_desc *ubifs_hash_get_desc(const struct ubifs_info *c)
{
	return ubifs_authenticated(c) ? __ubifs_hash_get_desc(c) : NULL;
}