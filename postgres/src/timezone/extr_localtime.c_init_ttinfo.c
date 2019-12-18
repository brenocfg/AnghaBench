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
struct ttinfo {int tt_isdst; int tt_desigidx; int tt_ttisstd; int tt_ttisut; int /*<<< orphan*/  tt_utoff; } ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */

__attribute__((used)) static void
init_ttinfo(struct ttinfo *s, int32 utoff, bool isdst, int desigidx)
{
	s->tt_utoff = utoff;
	s->tt_isdst = isdst;
	s->tt_desigidx = desigidx;
	s->tt_ttisstd = false;
	s->tt_ttisut = false;
}