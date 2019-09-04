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
struct string_list {char* string; } ;

/* Variables and functions */
 struct string_list* calloc (int,int) ; 

struct string_list *
new_string_list(size_t size)
{
	struct string_list *rval;

	rval = calloc(1, sizeof(struct string_list) + size);
	if (rval != NULL)
		rval->string = ((char *)rval) + sizeof(struct string_list);
	return (rval);
}