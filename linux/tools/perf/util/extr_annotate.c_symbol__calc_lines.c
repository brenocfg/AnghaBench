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
struct symbol {int dummy; } ;
struct rb_root {int dummy; } ;
struct map {int dummy; } ;
struct annotation_options {int dummy; } ;
struct annotation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotation__calc_lines (struct annotation*,struct map*,struct rb_root*,struct annotation_options*) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static void symbol__calc_lines(struct symbol *sym, struct map *map,
			       struct rb_root *root,
			       struct annotation_options *opts)
{
	struct annotation *notes = symbol__annotation(sym);

	annotation__calc_lines(notes, map, root, opts);
}