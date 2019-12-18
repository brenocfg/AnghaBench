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
struct script_desc {int /*<<< orphan*/  args; int /*<<< orphan*/  half_liner; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct script_desc*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void script_desc__delete(struct script_desc *s)
{
	zfree(&s->name);
	zfree(&s->half_liner);
	zfree(&s->args);
	free(s);
}