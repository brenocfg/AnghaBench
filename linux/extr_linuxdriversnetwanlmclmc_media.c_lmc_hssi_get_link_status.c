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
typedef  int /*<<< orphan*/  lmc_softc_t ;

/* Variables and functions */
 int lmc_ssi_get_link_status (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static int
lmc_hssi_get_link_status (lmc_softc_t * const sc)
{
    /*
     * We're using the same code as SSI since
     * they're practically the same
     */
    return lmc_ssi_get_link_status(sc);
}