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
struct TYPE_2__ {char* optname; void* offset; void* opttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  DUMMY_AM_ENUM_ONE ; 
 int /*<<< orphan*/  DummyIndexOptions ; 
 void* RELOPT_TYPE_BOOL ; 
 void* RELOPT_TYPE_ENUM ; 
 void* RELOPT_TYPE_INT ; 
 void* RELOPT_TYPE_REAL ; 
 void* RELOPT_TYPE_STRING ; 
 int /*<<< orphan*/  add_bool_reloption (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_enum_reloption (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_int_reloption (int /*<<< orphan*/ ,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_real_reloption (int /*<<< orphan*/ ,char*,char*,double,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_reloption_kind () ; 
 int /*<<< orphan*/  add_string_reloption (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_relopt_kind ; 
 TYPE_1__* di_relopt_tab ; 
 int /*<<< orphan*/  dummyAmEnumValues ; 
 void* offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_bool ; 
 int /*<<< orphan*/  option_enum ; 
 int /*<<< orphan*/  option_int ; 
 int /*<<< orphan*/  option_real ; 
 int /*<<< orphan*/  option_string_null_offset ; 
 int /*<<< orphan*/  option_string_val_offset ; 
 int /*<<< orphan*/  validate_string_option ; 

__attribute__((used)) static void
create_reloptions_table(void)
{
	di_relopt_kind = add_reloption_kind();

	add_int_reloption(di_relopt_kind, "option_int",
					  "Integer option for dummy_index_am",
					  10, -10, 100, AccessExclusiveLock);
	di_relopt_tab[0].optname = "option_int";
	di_relopt_tab[0].opttype = RELOPT_TYPE_INT;
	di_relopt_tab[0].offset = offsetof(DummyIndexOptions, option_int);

	add_real_reloption(di_relopt_kind, "option_real",
					   "Real option for dummy_index_am",
					   3.1415, -10, 100, AccessExclusiveLock);
	di_relopt_tab[1].optname = "option_real";
	di_relopt_tab[1].opttype = RELOPT_TYPE_REAL;
	di_relopt_tab[1].offset = offsetof(DummyIndexOptions, option_real);

	add_bool_reloption(di_relopt_kind, "option_bool",
					   "Boolean option for dummy_index_am",
					   true, AccessExclusiveLock);
	di_relopt_tab[2].optname = "option_bool";
	di_relopt_tab[2].opttype = RELOPT_TYPE_BOOL;
	di_relopt_tab[2].offset = offsetof(DummyIndexOptions, option_bool);

	add_enum_reloption(di_relopt_kind, "option_enum",
					   "Enum option for dummy_index_am",
					   dummyAmEnumValues,
					   DUMMY_AM_ENUM_ONE,
					   "Valid values are \"one\" and \"two\".",
					   AccessExclusiveLock);
	di_relopt_tab[3].optname = "option_enum";
	di_relopt_tab[3].opttype = RELOPT_TYPE_ENUM;
	di_relopt_tab[3].offset = offsetof(DummyIndexOptions, option_enum);

	add_string_reloption(di_relopt_kind, "option_string_val",
						 "String option for dummy_index_am with non-NULL default",
						 "DefaultValue", &validate_string_option,
						 AccessExclusiveLock);
	di_relopt_tab[4].optname = "option_string_val";
	di_relopt_tab[4].opttype = RELOPT_TYPE_STRING;
	di_relopt_tab[4].offset = offsetof(DummyIndexOptions,
									   option_string_val_offset);

	/*
	 * String option for dummy_index_am with NULL default, and without
	 * description.
	 */
	add_string_reloption(di_relopt_kind, "option_string_null",
						 NULL,	/* description */
						 NULL, &validate_string_option,
						 AccessExclusiveLock);
	di_relopt_tab[5].optname = "option_string_null";
	di_relopt_tab[5].opttype = RELOPT_TYPE_STRING;
	di_relopt_tab[5].offset = offsetof(DummyIndexOptions,
									   option_string_null_offset);
}