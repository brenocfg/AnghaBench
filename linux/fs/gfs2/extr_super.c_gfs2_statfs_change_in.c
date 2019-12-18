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
struct gfs2_statfs_change_host {void* sc_dinodes; void* sc_free; void* sc_total; } ;
struct gfs2_statfs_change {int /*<<< orphan*/  sc_dinodes; int /*<<< orphan*/  sc_free; int /*<<< orphan*/  sc_total; } ;

/* Variables and functions */
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 

void gfs2_statfs_change_in(struct gfs2_statfs_change_host *sc, const void *buf)
{
	const struct gfs2_statfs_change *str = buf;

	sc->sc_total = be64_to_cpu(str->sc_total);
	sc->sc_free = be64_to_cpu(str->sc_free);
	sc->sc_dinodes = be64_to_cpu(str->sc_dinodes);
}