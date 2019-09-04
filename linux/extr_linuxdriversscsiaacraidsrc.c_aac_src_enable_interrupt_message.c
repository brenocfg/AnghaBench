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
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ENABLE_INTERRUPT ; 
 int /*<<< orphan*/  aac_src_access_devreg (struct aac_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aac_src_enable_interrupt_message(struct aac_dev *dev)
{
	aac_src_access_devreg(dev, AAC_ENABLE_INTERRUPT);
}