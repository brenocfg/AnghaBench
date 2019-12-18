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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  fscrypt_bounce_page_pool ; 
 struct page* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct page *fscrypt_alloc_bounce_page(gfp_t gfp_flags)
{
	return mempool_alloc(fscrypt_bounce_page_pool, gfp_flags);
}