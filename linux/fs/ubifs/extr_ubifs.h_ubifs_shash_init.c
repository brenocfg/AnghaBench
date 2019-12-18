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
 int crypto_shash_init (struct shash_desc*) ; 
 scalar_t__ ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static inline int ubifs_shash_init(const struct ubifs_info *c,
				   struct shash_desc *desc)
{
	if (ubifs_authenticated(c))
		return crypto_shash_init(desc);
	else
		return 0;
}