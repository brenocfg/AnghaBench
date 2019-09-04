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
struct tc_service_curve {int /*<<< orphan*/  m2; int /*<<< orphan*/  d; int /*<<< orphan*/  m1; } ;
struct internal_sc {void* ism2; void* sm2; void* sm1; int /*<<< orphan*/  dx; int /*<<< orphan*/  dy; void* ism1; } ;

/* Variables and functions */
 int /*<<< orphan*/  d2dx (int /*<<< orphan*/ ) ; 
 void* m2ism (int /*<<< orphan*/ ) ; 
 void* m2sm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seg_x2y (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
sc2isc(struct tc_service_curve *sc, struct internal_sc *isc)
{
	isc->sm1  = m2sm(sc->m1);
	isc->ism1 = m2ism(sc->m1);
	isc->dx   = d2dx(sc->d);
	isc->dy   = seg_x2y(isc->dx, isc->sm1);
	isc->sm2  = m2sm(sc->m2);
	isc->ism2 = m2ism(sc->m2);
}