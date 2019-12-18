#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  relopt_string ;
typedef  int /*<<< orphan*/  relopt_real ;
typedef  int /*<<< orphan*/  relopt_int ;
struct TYPE_4__ {int type; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  namelen; int /*<<< orphan*/  kinds; int /*<<< orphan*/ * desc; void* name; } ;
typedef  TYPE_1__ relopt_gen ;
typedef  int /*<<< orphan*/  relopt_enum ;
typedef  int /*<<< orphan*/  relopt_bool ;
typedef  int /*<<< orphan*/  bits32 ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
#define  RELOPT_TYPE_BOOL 132 
#define  RELOPT_TYPE_ENUM 131 
#define  RELOPT_TYPE_INT 130 
#define  RELOPT_TYPE_REAL 129 
#define  RELOPT_TYPE_STRING 128 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* palloc (size_t) ; 
 void* pstrdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static relopt_gen *
allocate_reloption(bits32 kinds, int type, const char *name, const char *desc,
				   LOCKMODE lockmode)
{
	MemoryContext oldcxt;
	size_t		size;
	relopt_gen *newoption;

	oldcxt = MemoryContextSwitchTo(TopMemoryContext);

	switch (type)
	{
		case RELOPT_TYPE_BOOL:
			size = sizeof(relopt_bool);
			break;
		case RELOPT_TYPE_INT:
			size = sizeof(relopt_int);
			break;
		case RELOPT_TYPE_REAL:
			size = sizeof(relopt_real);
			break;
		case RELOPT_TYPE_ENUM:
			size = sizeof(relopt_enum);
			break;
		case RELOPT_TYPE_STRING:
			size = sizeof(relopt_string);
			break;
		default:
			elog(ERROR, "unsupported reloption type %d", type);
			return NULL;		/* keep compiler quiet */
	}

	newoption = palloc(size);

	newoption->name = pstrdup(name);
	if (desc)
		newoption->desc = pstrdup(desc);
	else
		newoption->desc = NULL;
	newoption->kinds = kinds;
	newoption->namelen = strlen(name);
	newoption->type = type;
	newoption->lockmode = lockmode;

	MemoryContextSwitchTo(oldcxt);

	return newoption;
}