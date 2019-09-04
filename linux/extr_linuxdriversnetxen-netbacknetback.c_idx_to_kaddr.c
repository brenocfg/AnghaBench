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
typedef  int /*<<< orphan*/  u16 ;
struct xenvif_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  idx_to_pfn (struct xenvif_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_to_kaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long idx_to_kaddr(struct xenvif_queue *queue,
					 u16 idx)
{
	return (unsigned long)pfn_to_kaddr(idx_to_pfn(queue, idx));
}