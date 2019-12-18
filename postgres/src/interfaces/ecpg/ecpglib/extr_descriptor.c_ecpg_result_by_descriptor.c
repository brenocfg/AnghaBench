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
struct descriptor {int /*<<< orphan*/ * result; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 struct descriptor* ecpg_find_desc (int,char const*) ; 

__attribute__((used)) static PGresult *
ecpg_result_by_descriptor(int line, const char *name)
{
	struct descriptor *desc = ecpg_find_desc(line, name);

	if (desc == NULL)
		return NULL;
	return desc->result;
}