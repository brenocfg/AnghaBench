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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_fault {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* swap_cluster_readahead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_fault*) ; 
 scalar_t__ swap_use_vma_readahead () ; 
 struct page* swap_vma_readahead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_fault*) ; 

struct page *swapin_readahead(swp_entry_t entry, gfp_t gfp_mask,
				struct vm_fault *vmf)
{
	return swap_use_vma_readahead() ?
			swap_vma_readahead(entry, gfp_mask, vmf) :
			swap_cluster_readahead(entry, gfp_mask, vmf);
}