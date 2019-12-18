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
typedef  int /*<<< orphan*/  u8 ;
struct ubifs_info {int dummy; } ;
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int crypto_shash_final (struct shash_desc*,int /*<<< orphan*/ *) ; 
 scalar_t__ ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static inline int ubifs_shash_final(const struct ubifs_info *c,
				    struct shash_desc *desc, u8 *out)
{
	return ubifs_authenticated(c) ? crypto_shash_final(desc, out) : 0;
}