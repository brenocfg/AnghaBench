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
struct anon_vma_chain {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 unsigned long vma_last_pgoff (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long avc_last_pgoff(struct anon_vma_chain *avc)
{
	return vma_last_pgoff(avc->vma);
}