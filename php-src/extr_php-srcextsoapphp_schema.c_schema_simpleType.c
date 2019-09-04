#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
typedef  TYPE_5__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlType ;
typedef  TYPE_6__* sdlPtr ;
typedef  int /*<<< orphan*/  encode ;
struct TYPE_37__ {int /*<<< orphan*/ * types; int /*<<< orphan*/ * encoders; } ;
struct TYPE_32__ {TYPE_5__* sdl_type; void* type_str; void* ns; } ;
struct TYPE_36__ {char* name; char* namens; void* kind; int /*<<< orphan*/ * elements; struct TYPE_36__* encode; int /*<<< orphan*/  to_zval; int /*<<< orphan*/  to_xml; TYPE_1__ details; } ;
struct TYPE_35__ {TYPE_2__* children; } ;
struct TYPE_34__ {int /*<<< orphan*/  name; struct TYPE_34__* next; struct TYPE_34__* children; int /*<<< orphan*/  properties; } ;
struct TYPE_33__ {scalar_t__ content; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 void* XSD_TYPEKIND_LIST ; 
 void* XSD_TYPEKIND_SIMPLE ; 
 void* XSD_TYPEKIND_UNION ; 
 int /*<<< orphan*/  create_encoder (TYPE_6__*,TYPE_5__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  delete_encoder ; 
 int /*<<< orphan*/  delete_type ; 
 void* emalloc (int) ; 
 void* estrdup (char*) ; 
 TYPE_4__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  schema_list (TYPE_6__*,TYPE_4__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  schema_restriction_simpleContent (TYPE_6__*,TYPE_4__*,TYPE_3__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  schema_union (TYPE_6__*,TYPE_4__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sdl_guess_convert_xml ; 
 int /*<<< orphan*/  sdl_guess_convert_zval ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* zend_hash_str_update_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int schema_simpleType(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr simpleType, sdlTypePtr cur_type)
{
	xmlNodePtr trav;
	xmlAttrPtr name, ns;

	ns = get_attribute(simpleType->properties, "targetNamespace");
	if (ns == NULL) {
		ns = tns;
	}

	name = get_attribute(simpleType->properties, "name");
	if (cur_type != NULL) {
		/* Anonymous type inside <element> or <restriction> */
		sdlTypePtr newType, ptr;

		newType = emalloc(sizeof(sdlType));
		memset(newType, 0, sizeof(sdlType));
		newType->kind = XSD_TYPEKIND_SIMPLE;
		if (name != NULL) {
			newType->name = estrdup((char*)name->children->content);
			newType->namens = estrdup((char*)ns->children->content);
		} else {
			newType->name = estrdup(cur_type->name);
			newType->namens = estrdup(cur_type->namens);
		}

		ptr = zend_hash_next_index_insert_ptr(sdl->types,  newType);

		if (sdl->encoders == NULL) {
			sdl->encoders = emalloc(sizeof(HashTable));
			zend_hash_init(sdl->encoders, 0, NULL, delete_encoder, 0);
		}
		cur_type->encode = emalloc(sizeof(encode));
		memset(cur_type->encode, 0, sizeof(encode));
		cur_type->encode->details.ns = estrdup(newType->namens);
		cur_type->encode->details.type_str = estrdup(newType->name);
		cur_type->encode->details.sdl_type = ptr;
		cur_type->encode->to_xml = sdl_guess_convert_xml;
		cur_type->encode->to_zval = sdl_guess_convert_zval;
		zend_hash_next_index_insert_ptr(sdl->encoders,  cur_type->encode);

		cur_type =ptr;

	} else if (name != NULL) {
		sdlTypePtr newType, ptr;

		newType = emalloc(sizeof(sdlType));
		memset(newType, 0, sizeof(sdlType));
		newType->kind = XSD_TYPEKIND_SIMPLE;
		newType->name = estrdup((char*)name->children->content);
		newType->namens = estrdup((char*)ns->children->content);

		if (cur_type == NULL) {
			ptr = zend_hash_next_index_insert_ptr(sdl->types, newType);
		} else {
			if (cur_type->elements == NULL) {
				cur_type->elements = emalloc(sizeof(HashTable));
				zend_hash_init(cur_type->elements, 0, NULL, delete_type, 0);
			}
			ptr = zend_hash_str_update_ptr(cur_type->elements, newType->name, strlen(newType->name), newType);
		}
		cur_type = ptr;

		create_encoder(sdl, cur_type, ns->children->content, name->children->content);
	} else {
		soap_error0(E_ERROR, "Parsing Schema: simpleType has no 'name' attribute");
	}

	trav = simpleType->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL) {
		if (node_is_equal(trav,"restriction")) {
			schema_restriction_simpleContent(sdl, tns, trav, cur_type, 1);
			trav = trav->next;
		} else if (node_is_equal(trav,"list")) {
			cur_type->kind = XSD_TYPEKIND_LIST;
			schema_list(sdl, tns, trav, cur_type);
			trav = trav->next;
		} else if (node_is_equal(trav,"union")) {
			cur_type->kind = XSD_TYPEKIND_UNION;
			schema_union(sdl, tns, trav, cur_type);
			trav = trav->next;
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in simpleType", trav->name);
		}
	} else {
		soap_error0(E_ERROR, "Parsing Schema: expected <restriction>, <list> or <union> in simpleType");
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in simpleType", trav->name);
	}

	return TRUE;
}