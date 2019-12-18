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
struct btf_type {int /*<<< orphan*/  info; } ;
struct btf {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 scalar_t__ BTF_KIND_STRUCT ; 
 int EINVAL ; 

__attribute__((used)) static int trie_check_btf(const struct bpf_map *map,
			  const struct btf *btf,
			  const struct btf_type *key_type,
			  const struct btf_type *value_type)
{
	/* Keys must have struct bpf_lpm_trie_key embedded. */
	return BTF_INFO_KIND(key_type->info) != BTF_KIND_STRUCT ?
	       -EINVAL : 0;
}