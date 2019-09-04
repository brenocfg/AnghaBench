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
 int /*<<< orphan*/  lmc_mii_writereg (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
lmc_t1_write (lmc_softc_t * const sc, int a, int d)
{
  lmc_mii_writereg (sc, 0, 17, a);
  lmc_mii_writereg (sc, 0, 18, d);
}