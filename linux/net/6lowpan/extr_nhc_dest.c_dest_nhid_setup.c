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
struct lowpan_nhc {int /*<<< orphan*/ * idmask; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOWPAN_NHC_DEST_ID_0 ; 
 int /*<<< orphan*/  LOWPAN_NHC_DEST_MASK_0 ; 

__attribute__((used)) static void dest_nhid_setup(struct lowpan_nhc *nhc)
{
	nhc->id[0] = LOWPAN_NHC_DEST_ID_0;
	nhc->idmask[0] = LOWPAN_NHC_DEST_MASK_0;
}