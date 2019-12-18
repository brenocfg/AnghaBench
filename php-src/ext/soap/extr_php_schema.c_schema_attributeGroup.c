#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
struct TYPE_31__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ smart_str ;
typedef  TYPE_6__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlType ;
typedef  int /*<<< orphan*/  sdlPtr ;
struct TYPE_33__ {int /*<<< orphan*/  attributeGroups; } ;
typedef  TYPE_7__ sdlCtx ;
typedef  TYPE_6__* sdlAttributePtr ;
typedef  int /*<<< orphan*/  sdlAttribute ;
struct TYPE_32__ {char* name; char* namens; int /*<<< orphan*/ * attributes; int /*<<< orphan*/  ref; } ;
struct TYPE_30__ {TYPE_1__* children; } ;
struct TYPE_29__ {int /*<<< orphan*/  name; struct TYPE_29__* next; struct TYPE_29__* children; int /*<<< orphan*/  doc; int /*<<< orphan*/  properties; } ;
struct TYPE_28__ {scalar_t__ href; } ;
struct TYPE_27__ {scalar_t__ content; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_attribute ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* emalloc (int) ; 
 void* estrdup (char*) ; 
 int /*<<< orphan*/  estrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  parse_namespace (scalar_t__,char**,char**) ; 
 int /*<<< orphan*/  schema_attribute (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_5__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_5__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_5__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_add_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,TYPE_6__*) ; 

__attribute__((used)) static int schema_attributeGroup(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr attrGroup, sdlTypePtr cur_type, sdlCtx *ctx)
{
	xmlNodePtr trav;
	xmlAttrPtr name, ref = NULL;


	name = get_attribute(attrGroup->properties, "name");
	if (name == NULL) {
		name = ref = get_attribute(attrGroup->properties, "ref");
	}
	if (name) {
		if (cur_type == NULL) {
			xmlAttrPtr ns;
			sdlTypePtr newType;
			smart_str key = {0};

			ns = get_attribute(attrGroup->properties, "targetNamespace");
			if (ns == NULL) {
				ns = tns;
			}
			newType = emalloc(sizeof(sdlType));
			memset(newType, 0, sizeof(sdlType));
			newType->name = estrdup((char*)name->children->content);
			newType->namens = estrdup((char*)ns->children->content);

			smart_str_appends(&key, newType->namens);
			smart_str_appendc(&key, ':');
			smart_str_appends(&key, newType->name);
			smart_str_0(&key);

			if (zend_hash_add_ptr(ctx->attributeGroups, key.s, newType) == NULL) {
				soap_error1(E_ERROR, "Parsing Schema: attributeGroup '%s' already defined", ZSTR_VAL(key.s));
			}
			cur_type = newType;
			smart_str_free(&key);
		} else if (ref) {
			sdlAttributePtr newAttr;
			char *group_name, *ns;
			smart_str key = {0};
			xmlNsPtr nsptr;

			if (cur_type->attributes == NULL) {
				cur_type->attributes = emalloc(sizeof(HashTable));
				zend_hash_init(cur_type->attributes, 0, NULL, delete_attribute, 0);
			}
			newAttr = emalloc(sizeof(sdlAttribute));
			memset(newAttr, 0, sizeof(sdlAttribute));

			parse_namespace(ref->children->content, &group_name, &ns);
			nsptr = xmlSearchNs(attrGroup->doc, attrGroup, BAD_CAST(ns));
			if (nsptr != NULL) {
				smart_str_appends(&key, (char*)nsptr->href);
			}
			smart_str_appendc(&key, ':');
			smart_str_appends(&key, group_name);
			smart_str_0(&key);
			newAttr->ref = estrndup(ZSTR_VAL(key.s), ZSTR_LEN(key.s));
			if (group_name) {efree(group_name);}
			if (ns) {efree(ns);}
			smart_str_free(&key);

			zend_hash_next_index_insert_ptr(cur_type->attributes, newAttr);
			cur_type = NULL;
		}
	} else{
		soap_error0(E_ERROR, "Parsing Schema: attributeGroup has no 'name' nor 'ref' attributes");
	}

	trav = attrGroup->children;
	if (trav != NULL && node_is_equal(trav, "annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	while (trav != NULL) {
		if (node_is_equal(trav,"attribute")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: attributeGroup has both 'ref' attribute and subattribute");
			}
			schema_attribute(sdl, tns, trav, cur_type, NULL);
		} else if (node_is_equal(trav,"attributeGroup")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: attributeGroup has both 'ref' attribute and subattribute");
			}
			schema_attributeGroup(sdl, tns, trav, cur_type, NULL);
		} else if (node_is_equal(trav,"anyAttribute")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: attributeGroup has both 'ref' attribute and subattribute");
			}
			/* TODO: <anyAttribute> support */
			trav = trav->next;
			break;
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in attributeGroup", trav->name);
		}
		trav = trav->next;
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in attributeGroup", trav->name);
	}
	return TRUE;
}