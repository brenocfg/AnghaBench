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
struct vo_internal {int external_renderloop_drive; } ;
struct vo {struct vo_internal* in; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*) ; 

void vo_disable_external_renderloop(struct vo *vo)
{
    struct vo_internal *in = vo->in;
    MP_VERBOSE(vo, "Disabling event driven renderloop!\n");
    in->external_renderloop_drive = false;
}