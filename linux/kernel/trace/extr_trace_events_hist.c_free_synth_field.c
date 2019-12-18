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
struct synth_field {struct synth_field* name; struct synth_field* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct synth_field*) ; 

__attribute__((used)) static void free_synth_field(struct synth_field *field)
{
	kfree(field->type);
	kfree(field->name);
	kfree(field);
}