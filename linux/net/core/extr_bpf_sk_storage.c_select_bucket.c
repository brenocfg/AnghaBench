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
struct bucket {int dummy; } ;
struct bpf_sk_storage_map {int /*<<< orphan*/  bucket_log; struct bucket* buckets; } ;
struct bpf_sk_storage_elem {int dummy; } ;

/* Variables and functions */
 size_t hash_ptr (struct bpf_sk_storage_elem*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bucket *select_bucket(struct bpf_sk_storage_map *smap,
				    struct bpf_sk_storage_elem *selem)
{
	return &smap->buckets[hash_ptr(selem, smap->bucket_log)];
}