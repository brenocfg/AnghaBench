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
struct dso {int /*<<< orphan*/  hit; } ;

/* Variables and functions */

__attribute__((used)) static bool dso__skip_buildid(struct dso *dso, int with_hits)
{
	return with_hits && !dso->hit;
}