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
struct typedefs {struct typedefs* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_ERROR ; 
 int /*<<< orphan*/  mmfatal (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct typedefs* types ; 

struct typedefs *
get_typedef(char *name)
{
	struct typedefs *this;

	for (this = types; this && strcmp(this->name, name) != 0; this = this->next);
	if (!this)
		mmfatal(PARSE_ERROR, "unrecognized data type name \"%s\"", name);

	return this;
}