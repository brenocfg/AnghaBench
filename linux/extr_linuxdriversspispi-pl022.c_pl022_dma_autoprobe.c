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
struct pl022 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int pl022_dma_autoprobe(struct pl022 *pl022)
{
	return 0;
}