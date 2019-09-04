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
struct page {int dummy; } ;
struct kmem_cache_node {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void remove_full(struct kmem_cache *s, struct kmem_cache_node *n,
					struct page *page) {}