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

__attribute__((used)) static int rsnd_ctu_id_sub(struct rsnd_mod *mod)
{
	/*
	 * ctu00: -> 0, ctu01: -> 1, ctu02: -> 2, ctu03: -> 3
	 * ctu10: -> 0, ctu11: -> 1, ctu12: -> 2, ctu13: -> 3
	 */
	return mod->id % 4;
}