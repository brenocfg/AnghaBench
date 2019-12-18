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
typedef  int /*<<< orphan*/  u32 ;
struct modsig {int hash_algo; int /*<<< orphan*/  digest_size; int /*<<< orphan*/ * digest; } ;
typedef  enum hash_algo { ____Placeholder_hash_algo } hash_algo ;

/* Variables and functions */

int ima_get_modsig_digest(const struct modsig *modsig, enum hash_algo *algo,
			  const u8 **digest, u32 *digest_size)
{
	*algo = modsig->hash_algo;
	*digest = modsig->digest;
	*digest_size = modsig->digest_size;

	return 0;
}