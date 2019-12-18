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
struct rsnd_mod {int id; } ;

/* Variables and functions */

__attribute__((used)) static int rsnd_ctu_id(struct rsnd_mod *mod)
{
	/*
	 * ctu00: -> 0, ctu01: -> 0, ctu02: -> 0, ctu03: -> 0
	 * ctu10: -> 1, ctu11: -> 1, ctu12: -> 1, ctu13: -> 1
	 */
	return mod->id / 4;
}