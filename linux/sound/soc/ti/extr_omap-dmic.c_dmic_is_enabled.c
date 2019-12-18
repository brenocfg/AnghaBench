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
struct omap_dmic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DMIC_CTRL_REG ; 
 int OMAP_DMIC_UP_ENABLE_MASK ; 
 int omap_dmic_read (struct omap_dmic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dmic_is_enabled(struct omap_dmic *dmic)
{
	return omap_dmic_read(dmic, OMAP_DMIC_CTRL_REG) &
						OMAP_DMIC_UP_ENABLE_MASK;
}