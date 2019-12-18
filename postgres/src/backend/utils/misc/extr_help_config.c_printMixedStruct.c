#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {char* name; size_t context; size_t group; int vartype; int /*<<< orphan*/ * long_desc; int /*<<< orphan*/ * short_desc; } ;
struct TYPE_15__ {int /*<<< orphan*/  boot_val; } ;
struct TYPE_12__ {char* boot_val; } ;
struct TYPE_11__ {double reset_val; double min; double max; } ;
struct TYPE_10__ {int reset_val; int min; int max; } ;
struct TYPE_9__ {int /*<<< orphan*/  reset_val; } ;
struct TYPE_14__ {TYPE_5__ generic; TYPE_8__ _enum; TYPE_4__ string; TYPE_3__ real; TYPE_2__ integer; TYPE_1__ _bool; } ;
typedef  TYPE_6__ mixedStruct ;

/* Variables and functions */
 char** GucContext_Names ; 
#define  PGC_BOOL 132 
#define  PGC_ENUM 131 
#define  PGC_INT 130 
#define  PGC_REAL 129 
#define  PGC_STRING 128 
 char* _ (int /*<<< orphan*/ *) ; 
 char* config_enum_lookup_by_value (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** config_group_names ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  write_stderr (char*) ; 

__attribute__((used)) static void
printMixedStruct(mixedStruct *structToPrint)
{
	printf("%s\t%s\t%s\t",
		   structToPrint->generic.name,
		   GucContext_Names[structToPrint->generic.context],
		   _(config_group_names[structToPrint->generic.group]));

	switch (structToPrint->generic.vartype)
	{

		case PGC_BOOL:
			printf("BOOLEAN\t%s\t\t\t",
				   (structToPrint->_bool.reset_val == 0) ?
				   "FALSE" : "TRUE");
			break;

		case PGC_INT:
			printf("INTEGER\t%d\t%d\t%d\t",
				   structToPrint->integer.reset_val,
				   structToPrint->integer.min,
				   structToPrint->integer.max);
			break;

		case PGC_REAL:
			printf("REAL\t%g\t%g\t%g\t",
				   structToPrint->real.reset_val,
				   structToPrint->real.min,
				   structToPrint->real.max);
			break;

		case PGC_STRING:
			printf("STRING\t%s\t\t\t",
				   structToPrint->string.boot_val ? structToPrint->string.boot_val : "");
			break;

		case PGC_ENUM:
			printf("ENUM\t%s\t\t\t",
				   config_enum_lookup_by_value(&structToPrint->_enum,
											   structToPrint->_enum.boot_val));
			break;

		default:
			write_stderr("internal error: unrecognized run-time parameter type\n");
			break;
	}

	printf("%s\t%s\n",
		   (structToPrint->generic.short_desc == NULL) ? "" : _(structToPrint->generic.short_desc),
		   (structToPrint->generic.long_desc == NULL) ? "" : _(structToPrint->generic.long_desc));
}