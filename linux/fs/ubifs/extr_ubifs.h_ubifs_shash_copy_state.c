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
 int __ubifs_shash_copy_state (struct ubifs_info const*,struct shash_desc*,struct shash_desc*) ; 
 scalar_t__ ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static inline int ubifs_shash_copy_state(const struct ubifs_info *c,
					   struct shash_desc *src,
					   struct shash_desc *target)
{
	if (ubifs_authenticated(c))
		return __ubifs_shash_copy_state(c, src, target);
	else
		return 0;
}