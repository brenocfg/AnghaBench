#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  TYPE_5__* xmlAttrPtr ;
struct TYPE_48__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ smart_str ;
typedef  TYPE_7__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlType ;
typedef  TYPE_8__* sdlPtr ;
typedef  TYPE_9__* sdlContentModelPtr ;
typedef  int /*<<< orphan*/  sdlContentModel ;
struct TYPE_44__ {int /*<<< orphan*/ * content; int /*<<< orphan*/  group_ref; } ;
struct TYPE_51__ {void* kind; TYPE_2__ u; } ;
struct TYPE_50__ {int /*<<< orphan*/ * groups; } ;
struct TYPE_49__ {TYPE_9__* model; } ;
struct TYPE_47__ {TYPE_1__* children; } ;
struct TYPE_46__ {int /*<<< orphan*/  name; struct TYPE_46__* next; struct TYPE_46__* children; int /*<<< orphan*/  properties; int /*<<< orphan*/  doc; } ;
struct TYPE_45__ {scalar_t__ href; } ;
struct TYPE_43__ {scalar_t__ content; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 void* XSD_CONTENT_ALL ; 
 void* XSD_CONTENT_CHOICE ; 
 void* XSD_CONTENT_GROUP_REF ; 
 void* XSD_CONTENT_SEQUENCE ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_model ; 
 int /*<<< orphan*/  delete_type ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* emalloc (int) ; 
 int /*<<< orphan*/  estrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  parse_namespace (scalar_t__,char**,char**) ; 
 int /*<<< orphan*/  schema_all (TYPE_8__*,TYPE_5__*,TYPE_4__*,TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  schema_choice (TYPE_8__*,TYPE_5__*,TYPE_4__*,TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  schema_min_max (TYPE_4__*,TYPE_9__*) ; 
 int /*<<< orphan*/  schema_sequence (TYPE_8__*,TYPE_5__*,TYPE_4__*,TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_6__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_6__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_6__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,TYPE_9__*) ; 

__attribute__((used)) static int schema_group(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr groupType, sdlTypePtr cur_type, sdlContentModelPtr model)
{
	xmlNodePtr trav;
	xmlAttrPtr ns, name, ref = NULL;
	sdlContentModelPtr newModel = NULL;

	ns = get_attribute(groupType->properties, "targetNamespace");
	if (ns == NULL) {
		ns = tns;
	}

	name = get_attribute(groupType->properties, "name");
	if (name == NULL) {
		name = ref = get_attribute(groupType->properties, "ref");
	}

	if (name) {
		smart_str key = {0};

		if (ref) {
			char *type, *ns;
			xmlNsPtr nsptr;

			parse_namespace(ref->children->content, &type, &ns);
			nsptr = xmlSearchNs(groupType->doc, groupType, BAD_CAST(ns));
			if (nsptr != NULL) {
				smart_str_appends(&key, (char*)nsptr->href);
			} else {
				xmlAttrPtr ns = get_attribute(groupType->properties, "targetNamespace");
				if (ns == NULL) {
					ns = tns;
				}
				if (ns) {
					smart_str_appends(&key, (char*)ns->children->content);
				}
			}
			smart_str_appendc(&key, ':');
			smart_str_appends(&key, type);
			smart_str_0(&key);

			newModel = emalloc(sizeof(sdlContentModel));
			newModel->kind = XSD_CONTENT_GROUP_REF;
			newModel->u.group_ref = estrndup(ZSTR_VAL(key.s), ZSTR_LEN(key.s));

			if (type) {efree(type);}
			if (ns) {efree(ns);}
		} else {
			newModel = emalloc(sizeof(sdlContentModel));
			newModel->kind = XSD_CONTENT_SEQUENCE; /* will be redefined */
			newModel->u.content = emalloc(sizeof(HashTable));
			zend_hash_init(newModel->u.content, 0, NULL, delete_model, 0);

			smart_str_appends(&key, (char*)ns->children->content);
			smart_str_appendc(&key, ':');
			smart_str_appends(&key, (char*)name->children->content);
			smart_str_0(&key);
		}

		if (cur_type == NULL) {
			sdlTypePtr newType;

			newType = emalloc(sizeof(sdlType));
			memset(newType, 0, sizeof(sdlType));

			if (sdl->groups == NULL) {
				sdl->groups = emalloc(sizeof(HashTable));
				zend_hash_init(sdl->groups, 0, NULL, delete_type, 0);
			}
			if (zend_hash_add_ptr(sdl->groups, key.s, newType) == NULL) {
				soap_error1(E_ERROR, "Parsing Schema: group '%s' already defined", ZSTR_VAL(key.s));
			}

			cur_type = newType;
		}
		smart_str_free(&key);

		if (model == NULL) {
			cur_type->model = newModel;
		} else {
			zend_hash_next_index_insert_ptr(model->u.content, newModel);
		}
	} else {
		soap_error0(E_ERROR, "Parsing Schema: group has no 'name' nor 'ref' attributes");
	}

	schema_min_max(groupType, newModel);

	trav = groupType->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL) {
		if (node_is_equal(trav,"choice")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: group has both 'ref' attribute and subcontent");
			}
			newModel->kind = XSD_CONTENT_CHOICE;
			schema_choice(sdl, tns, trav, cur_type, newModel);
			trav = trav->next;
		} else if (node_is_equal(trav,"sequence")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: group has both 'ref' attribute and subcontent");
			}
			newModel->kind = XSD_CONTENT_SEQUENCE;
			schema_sequence(sdl, tns, trav, cur_type, newModel);
			trav = trav->next;
		} else if (node_is_equal(trav,"all")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: group has both 'ref' attribute and subcontent");
			}
			newModel->kind = XSD_CONTENT_ALL;
			schema_all(sdl, tns, trav, cur_type, newModel);
			trav = trav->next;
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in group", trav->name);
		}
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in group", trav->name);
	}
	return TRUE;
}