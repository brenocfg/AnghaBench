#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlAttrPtr ;
typedef  TYPE_4__* sdlRestrictionCharPtr ;
typedef  int /*<<< orphan*/  sdlRestrictionChar ;
struct TYPE_13__ {int fixed; int /*<<< orphan*/  value; } ;
struct TYPE_12__ {TYPE_1__* children; } ;
struct TYPE_11__ {int /*<<< orphan*/  properties; } ;
struct TYPE_10__ {scalar_t__ content; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int FALSE ; 
 int TRUE ; 
 TYPE_4__* emalloc (int) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 TYPE_3__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int schema_restriction_var_char(xmlNodePtr val, sdlRestrictionCharPtr *valptr)
{
	xmlAttrPtr fixed, value;

	if ((*valptr) == NULL) {
		(*valptr) = emalloc(sizeof(sdlRestrictionChar));
	}
	memset((*valptr), 0, sizeof(sdlRestrictionChar));

	fixed = get_attribute(val->properties, "fixed");
	(*valptr)->fixed = FALSE;
	if (fixed != NULL) {
		if (!strncmp((char*)fixed->children->content, "true", sizeof("true")) ||
		    !strncmp((char*)fixed->children->content, "1", sizeof("1"))) {
			(*valptr)->fixed = TRUE;
		}
	}

	value = get_attribute(val->properties, "value");
	if (value == NULL) {
		soap_error0(E_ERROR, "Parsing Schema: missing restriction value");
	}

	(*valptr)->value = estrdup((char*)value->children->content);
	return TRUE;
}