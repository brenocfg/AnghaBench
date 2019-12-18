#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_values; int /*<<< orphan*/  enum_values; } ;
typedef  TYPE_1__ TypeCacheEnumData ;
struct TYPE_8__ {int /*<<< orphan*/  enum_oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ EnumItem ;

/* Variables and functions */
 TYPE_2__* bsearch (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_oid_cmp ; 

__attribute__((used)) static EnumItem *
find_enumitem(TypeCacheEnumData *enumdata, Oid arg)
{
	EnumItem	srch;

	/* On some versions of Solaris, bsearch of zero items dumps core */
	if (enumdata->num_values <= 0)
		return NULL;

	srch.enum_oid = arg;
	return bsearch(&srch, enumdata->enum_values, enumdata->num_values,
				   sizeof(EnumItem), enum_oid_cmp);
}