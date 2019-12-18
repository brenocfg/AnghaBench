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
struct bpf_program {int /*<<< orphan*/  section_name; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *__bpf_program__pin_name(struct bpf_program *prog)
{
	char *name, *p;

	name = p = strdup(prog->section_name);
	while ((p = strchr(p, '/')))
		*p = '_';

	return name;
}