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
struct omap_mcpdm {int dummy; } ;

/* Variables and functions */
 int MCPDM_PDM_DN_MASK ; 
 int MCPDM_PDM_UP_MASK ; 
 int /*<<< orphan*/  MCPDM_REG_CTRL ; 
 int omap_mcpdm_read (struct omap_mcpdm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int omap_mcpdm_active(struct omap_mcpdm *mcpdm)
{
	return omap_mcpdm_read(mcpdm, MCPDM_REG_CTRL) &
					(MCPDM_PDM_DN_MASK | MCPDM_PDM_UP_MASK);
}