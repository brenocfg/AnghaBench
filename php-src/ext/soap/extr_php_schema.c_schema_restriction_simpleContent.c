#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_26__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
typedef  TYPE_5__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlRestrictions ;
typedef  TYPE_6__* sdlRestrictionCharPtr ;
typedef  int /*<<< orphan*/  sdlPtr ;
struct TYPE_36__ {int /*<<< orphan*/  value; } ;
struct TYPE_35__ {TYPE_26__* restrictions; int /*<<< orphan*/  encode; } ;
struct TYPE_34__ {TYPE_1__* children; } ;
struct TYPE_33__ {int /*<<< orphan*/  name; struct TYPE_33__* next; struct TYPE_33__* children; int /*<<< orphan*/  doc; int /*<<< orphan*/  properties; } ;
struct TYPE_32__ {int /*<<< orphan*/  href; } ;
struct TYPE_31__ {int /*<<< orphan*/ * enumeration; TYPE_6__* pattern; TYPE_6__* whiteSpace; int /*<<< orphan*/  maxLength; int /*<<< orphan*/  minLength; int /*<<< orphan*/  length; int /*<<< orphan*/  fractionDigits; int /*<<< orphan*/  totalDigits; int /*<<< orphan*/  maxInclusive; int /*<<< orphan*/  maxExclusive; int /*<<< orphan*/  minInclusive; int /*<<< orphan*/  minExclusive; } ;
struct TYPE_30__ {int /*<<< orphan*/  content; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  delete_restriction_var_char ; 
 int /*<<< orphan*/  delete_restriction_var_char_int (TYPE_6__*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* emalloc (int) ; 
 TYPE_4__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_create_encoder (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_26__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  parse_namespace (int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  schema_attribute (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_attributeGroup (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_restriction_var_char (TYPE_3__*,TYPE_6__**) ; 
 int /*<<< orphan*/  schema_restriction_var_int (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_simpleType (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_str_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static int schema_restriction_simpleContent(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr restType, sdlTypePtr cur_type, int simpleType)
{
	xmlNodePtr trav;
	xmlAttrPtr base;

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
	} else if (!simpleType) {
		soap_error0(E_ERROR, "Parsing Schema: restriction has no 'base' attribute");
	}

	if (cur_type->restrictions == NULL) {
		cur_type->restrictions = emalloc(sizeof(sdlRestrictions));
		memset(cur_type->restrictions, 0, sizeof(sdlRestrictions));
	}

	trav = restType->children;
	if (trav != NULL && node_is_equal(trav, "annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL && node_is_equal(trav, "simpleType")) {
		schema_simpleType(sdl, tns, trav, cur_type);
		trav = trav->next;
	}
	while (trav != NULL) {
		if (node_is_equal(trav, "minExclusive")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->minExclusive);
		} else if (node_is_equal(trav, "minInclusive")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->minInclusive);
		} else if (node_is_equal(trav, "maxExclusive")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->maxExclusive);
		} else if (node_is_equal(trav, "maxInclusive")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->maxInclusive);
		} else if (node_is_equal(trav, "totalDigits")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->totalDigits);
		} else if (node_is_equal(trav, "fractionDigits")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->fractionDigits);
		} else if (node_is_equal(trav, "length")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->length);
		} else if (node_is_equal(trav, "minLength")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->minLength);
		} else if (node_is_equal(trav, "maxLength")) {
			schema_restriction_var_int(trav, &cur_type->restrictions->maxLength);
		} else if (node_is_equal(trav, "whiteSpace")) {
			schema_restriction_var_char(trav, &cur_type->restrictions->whiteSpace);
		} else if (node_is_equal(trav, "pattern")) {
			schema_restriction_var_char(trav, &cur_type->restrictions->pattern);
		} else if (node_is_equal(trav, "enumeration")) {
			sdlRestrictionCharPtr enumval = NULL;

			schema_restriction_var_char(trav, &enumval);
			if (cur_type->restrictions->enumeration == NULL) {
				cur_type->restrictions->enumeration = emalloc(sizeof(HashTable));
				zend_hash_init(cur_type->restrictions->enumeration, 0, NULL, delete_restriction_var_char, 0);
			}
			if (zend_hash_str_add_ptr(cur_type->restrictions->enumeration, enumval->value, strlen(enumval->value), enumval) == NULL) {
				delete_restriction_var_char_int(enumval);
			}
		} else {
			break;
		}
		trav = trav->next;
	}
	if (!simpleType) {
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
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in restriction", trav->name);
	}

	return TRUE;
}