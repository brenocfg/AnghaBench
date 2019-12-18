#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlAttrPtr ;
typedef  TYPE_2__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlPtr ;
struct TYPE_11__ {int /*<<< orphan*/  kind; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; struct TYPE_10__* next; struct TYPE_10__* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  XSD_TYPEKIND_EXTENSION ; 
 int /*<<< orphan*/  XSD_TYPEKIND_RESTRICTION ; 
 scalar_t__ node_is_equal (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  schema_extension_simpleContent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  schema_restriction_simpleContent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int schema_simpleContent(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr simpCompType, sdlTypePtr cur_type)
{
	xmlNodePtr trav;

	trav = simpCompType->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL) {
		if (node_is_equal(trav, "restriction")) {
			cur_type->kind = XSD_TYPEKIND_RESTRICTION;
			schema_restriction_simpleContent(sdl, tns, trav, cur_type, 0);
			trav = trav->next;
		} else if (node_is_equal(trav, "extension")) {
			cur_type->kind = XSD_TYPEKIND_EXTENSION;
			schema_extension_simpleContent(sdl, tns, trav, cur_type);
			trav = trav->next;
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in simpleContent", trav->name);
		}
	} else {
		soap_error0(E_ERROR, "Parsing Schema: expected <restriction> or <extension> in simpleContent");
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in simpleContent", trav->name);
	}

	return TRUE;
}