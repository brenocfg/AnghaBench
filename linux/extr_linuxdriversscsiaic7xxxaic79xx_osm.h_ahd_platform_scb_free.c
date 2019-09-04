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
struct scb {int dummy; } ;
struct ahd_softc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_RESOURCE_SHORTAGE ; 

__attribute__((used)) static inline void
ahd_platform_scb_free(struct ahd_softc *ahd, struct scb *scb)
{
	ahd->flags &= ~AHD_RESOURCE_SHORTAGE;
}