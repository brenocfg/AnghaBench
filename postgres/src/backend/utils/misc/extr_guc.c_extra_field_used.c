#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct config_string {void* reset_extra; } ;
struct config_real {void* reset_extra; } ;
struct config_int {void* reset_extra; } ;
struct config_generic {void* extra; int vartype; TYPE_3__* stack; } ;
struct config_enum {void* reset_extra; } ;
struct config_bool {void* reset_extra; } ;
struct TYPE_5__ {void* extra; } ;
struct TYPE_4__ {void* extra; } ;
struct TYPE_6__ {TYPE_2__ masked; TYPE_1__ prior; struct TYPE_6__* prev; } ;
typedef  TYPE_3__ GucStack ;

/* Variables and functions */
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 

__attribute__((used)) static bool
extra_field_used(struct config_generic *gconf, void *extra)
{
	GucStack   *stack;

	if (extra == gconf->extra)
		return true;
	switch (gconf->vartype)
	{
		case PGC_BOOL:
			if (extra == ((struct config_bool *) gconf)->reset_extra)
				return true;
			break;
		case PGC_INT:
			if (extra == ((struct config_int *) gconf)->reset_extra)
				return true;
			break;
		case PGC_REAL:
			if (extra == ((struct config_real *) gconf)->reset_extra)
				return true;
			break;
		case PGC_STRING:
			if (extra == ((struct config_string *) gconf)->reset_extra)
				return true;
			break;
		case PGC_ENUM:
			if (extra == ((struct config_enum *) gconf)->reset_extra)
				return true;
			break;
	}
	for (stack = gconf->stack; stack; stack = stack->prev)
	{
		if (extra == stack->prior.extra ||
			extra == stack->masked.extra)
			return true;
	}

	return false;
}