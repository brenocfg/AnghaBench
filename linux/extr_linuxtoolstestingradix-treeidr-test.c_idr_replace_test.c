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

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  idr ; 
 int /*<<< orphan*/  idr_alloc (int /*<<< orphan*/ *,void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void idr_replace_test(void)
{
	DEFINE_IDR(idr);

	idr_alloc(&idr, (void *)-1, 10, 11, GFP_KERNEL);
	idr_replace(&idr, &idr, 10);

	idr_destroy(&idr);
}