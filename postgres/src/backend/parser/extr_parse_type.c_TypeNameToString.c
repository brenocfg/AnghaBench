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
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  appendTypeNameToBuffer (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

char *
TypeNameToString(const TypeName *typeName)
{
	StringInfoData string;

	initStringInfo(&string);
	appendTypeNameToBuffer(typeName, &string);
	return string.data;
}