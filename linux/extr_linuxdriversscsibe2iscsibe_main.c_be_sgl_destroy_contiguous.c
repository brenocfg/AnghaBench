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
struct be_dma_mem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void be_sgl_destroy_contiguous(struct be_dma_mem *sgl)
{
	memset(sgl, 0, sizeof(*sgl));
}