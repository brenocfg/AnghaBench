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
struct nft_rhash_elem {int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_set_ext_key (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 nft_rhash_obj(const void *data, u32 len, u32 seed)
{
	const struct nft_rhash_elem *he = data;

	return jhash(nft_set_ext_key(&he->ext), len, seed);
}