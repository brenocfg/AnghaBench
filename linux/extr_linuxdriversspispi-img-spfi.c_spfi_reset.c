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
struct img_spfi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPFI_CONTROL ; 
 int /*<<< orphan*/  SPFI_CONTROL_SOFT_RESET ; 
 int /*<<< orphan*/  spfi_writel (struct img_spfi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void spfi_reset(struct img_spfi *spfi)
{
	spfi_writel(spfi, SPFI_CONTROL_SOFT_RESET, SPFI_CONTROL);
	spfi_writel(spfi, 0, SPFI_CONTROL);
}