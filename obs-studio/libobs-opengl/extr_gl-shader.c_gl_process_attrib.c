#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct shader_attrib {int /*<<< orphan*/ * name; int /*<<< orphan*/  index; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct gs_shader {int /*<<< orphan*/  attribs; } ;
struct TYPE_2__ {scalar_t__ capacity; scalar_t__ len; int /*<<< orphan*/ * array; } ;
struct gl_parser_attrib {TYPE_1__ name; int /*<<< orphan*/  mapping; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct shader_attrib*) ; 
 int /*<<< orphan*/  get_attrib_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool gl_process_attrib(struct gs_shader *program,
				     struct gl_parser_attrib *pa)
{
	struct shader_attrib attrib = {0};

	/* don't parse output attributes */
	if (!pa->input)
		return true;

	get_attrib_type(pa->mapping, &attrib.type, &attrib.index);
	attrib.name = pa->name.array;

	pa->name.array = NULL;
	pa->name.len = 0;
	pa->name.capacity = 0;

	da_push_back(program->attribs, &attrib);
	return true;
}