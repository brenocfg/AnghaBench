#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
typedef  TYPE_5__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlPtr ;
struct TYPE_36__ {int /*<<< orphan*/  encode; } ;
struct TYPE_35__ {TYPE_1__* children; } ;
struct TYPE_34__ {int /*<<< orphan*/  name; struct TYPE_34__* next; struct TYPE_34__* children; int /*<<< orphan*/  doc; int /*<<< orphan*/  properties; } ;
struct TYPE_33__ {int /*<<< orphan*/  href; } ;
struct TYPE_32__ {int /*<<< orphan*/  content; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  efree (char*) ; 
 TYPE_4__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_create_encoder (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ node_is_equal (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  parse_namespace (int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  schema_all (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_attribute (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_attributeGroup (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_choice (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_group (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_sequence (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int schema_restriction_complexContent(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr restType, sdlTypePtr cur_type)
{
	xmlAttrPtr base;
	xmlNodePtr trav;

	base = get_attribute(restType->properties, "base");
	if (base != NULL) {
		char *type, *ns;
		xmlNsPtr nsptr;

		parse_namespace(base->children->content, &type, &ns);
		nsptr = xmlSearchNs(restType->doc, restType, BAD_CAST(ns));
		if (nsptr != NULL) {
			cur_type->encode = get_create_encoder(sdl, cur_type, nsptr->href, BAD_CAST(type));
		}
		if (type) {efree(type);}
		if (ns) {efree(ns);}
	} else {
		soap_error0(E_ERROR, "Parsing Schema: restriction has no 'base' attribute");
	}

	trav = restType->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL) {
		if (node_is_equal(trav,"group")) {
			schema_group(sdl, tns, trav, cur_type, NULL);
			trav = trav->next;
		} else if (node_is_equal(trav,"all")) {
			schema_all(sdl, tns, trav, cur_type, NULL);
			trav = trav->next;
		} else if (node_is_equal(trav,"choice")) {
			schema_choice(sdl, tns, trav, cur_type, NULL);
			trav = trav->next;
		} else if (node_is_equal(trav,"sequence")) {
			schema_sequence(sdl, tns, trav, cur_type, NULL);
			trav = trav->next;
		}
	}
	while (trav != NULL) {
		if (node_is_equal(trav,"attribute")) {
			schema_attribute(sdl, tns, trav, cur_type, NULL);
		} else if (node_is_equal(trav,"attributeGroup")) {
			schema_attributeGroup(sdl, tns, trav, cur_type, NULL);
		} else if (node_is_equal(trav,"anyAttribute")) {
			/* TODO: <anyAttribute> support */
			trav = trav->next;
			break;
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in restriction", trav->name);
		}
		trav = trav->next;
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in restriction", trav->name);
	}

	return TRUE;
}