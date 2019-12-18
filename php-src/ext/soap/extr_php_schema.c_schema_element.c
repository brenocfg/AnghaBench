#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlNsPtr ;
typedef  TYPE_4__* xmlNodePtr ;
typedef  TYPE_5__* xmlAttrPtr ;
struct TYPE_45__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ smart_str ;
typedef  TYPE_7__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlType ;
typedef  TYPE_8__* sdlPtr ;
typedef  TYPE_7__* sdlContentModelPtr ;
typedef  int /*<<< orphan*/  sdlContentModel ;
struct TYPE_47__ {int /*<<< orphan*/ * elements; } ;
struct TYPE_40__ {int /*<<< orphan*/ * content; TYPE_7__* element; } ;
struct TYPE_46__ {char* namens; char* name; int nillable; scalar_t__ form; int /*<<< orphan*/  encode; void* def; void* fixed; TYPE_1__ u; int /*<<< orphan*/  kind; int /*<<< orphan*/ * elements; int /*<<< orphan*/  ref; } ;
struct TYPE_44__ {TYPE_2__* children; } ;
struct TYPE_43__ {struct TYPE_43__* next; int /*<<< orphan*/  name; struct TYPE_43__* children; int /*<<< orphan*/  doc; struct TYPE_43__* parent; TYPE_5__* properties; } ;
struct TYPE_42__ {scalar_t__ href; } ;
struct TYPE_41__ {scalar_t__ content; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 void* FALSE ; 
 int /*<<< orphan*/  SCHEMA_NAMESPACE ; 
 int TRUE ; 
 int /*<<< orphan*/  XSD_CONTENT_ELEMENT ; 
 scalar_t__ XSD_FORM_DEFAULT ; 
 void* XSD_FORM_QUALIFIED ; 
 void* XSD_FORM_UNQUALIFIED ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_type ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* emalloc (int) ; 
 void* estrdup (char*) ; 
 int /*<<< orphan*/  estrndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* get_attribute (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  get_create_encoder (TYPE_8__*,TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal (TYPE_4__*,char*) ; 
 scalar_t__ node_is_equal_ex (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_namespace (scalar_t__,char**,char**) ; 
 int /*<<< orphan*/  schema_complexType (TYPE_8__*,TYPE_5__*,TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  schema_min_max (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  schema_simpleType (TYPE_8__*,TYPE_5__*,TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_6__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_6__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_6__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stricmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_3__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_add_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,TYPE_7__*) ; 

__attribute__((used)) static int schema_element(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr element, sdlTypePtr cur_type, sdlContentModelPtr model)
{
	xmlNodePtr trav;
	xmlAttrPtr attrs, attr, ns, name, type, ref = NULL;

	attrs = element->properties;
	ns = get_attribute(attrs, "targetNamespace");
	if (ns == NULL) {
		ns = tns;
	}

	name = get_attribute(attrs, "name");
	if (name == NULL) {
		name = ref = get_attribute(attrs, "ref");
	}

	if (name) {
		HashTable *addHash;
		sdlTypePtr newType;
		smart_str key = {0};

		newType = emalloc(sizeof(sdlType));
		memset(newType, 0, sizeof(sdlType));

		if (ref) {
			smart_str nscat = {0};
			char *type, *ns;
			xmlNsPtr nsptr;

			parse_namespace(ref->children->content, &type, &ns);
			nsptr = xmlSearchNs(element->doc, element, BAD_CAST(ns));
			if (nsptr != NULL) {
				smart_str_appends(&nscat, (char*)nsptr->href);
				newType->namens = estrdup((char*)nsptr->href);
			} else {
				xmlAttrPtr ns = get_attribute(attrs, "targetNamespace");
				if (ns == NULL) {
					ns = tns;
				}
				if (ns) {
					smart_str_appends(&nscat, (char*)ns->children->content);
				}
			}
			smart_str_appendc(&nscat, ':');
			smart_str_appends(&nscat, type);
			newType->name = estrdup(type);
			smart_str_0(&nscat);
			if (type) {efree(type);}
			if (ns) {efree(ns);}
			newType->ref = estrndup(ZSTR_VAL(nscat.s), ZSTR_LEN(nscat.s));
			smart_str_free(&nscat);
		} else {
			newType->name = estrdup((char*)name->children->content);
			newType->namens = estrdup((char*)ns->children->content);
		}

		newType->nillable = FALSE;

		if (cur_type == NULL) {
			if (sdl->elements == NULL) {
				sdl->elements = emalloc(sizeof(HashTable));
				zend_hash_init(sdl->elements, 0, NULL, delete_type, 0);
			}
			addHash = sdl->elements;
			smart_str_appends(&key, newType->namens);
			smart_str_appendc(&key, ':');
			smart_str_appends(&key, newType->name);
		} else {
			if (cur_type->elements == NULL) {
				cur_type->elements = emalloc(sizeof(HashTable));
				zend_hash_init(cur_type->elements, 0, NULL, delete_type, 0);
			}
			addHash = cur_type->elements;
			smart_str_appends(&key, newType->name);
		}

		smart_str_0(&key);
		if (zend_hash_add_ptr(addHash, key.s, newType) == NULL) {
			if (cur_type == NULL) {
				soap_error1(E_ERROR, "Parsing Schema: element '%s' already defined", ZSTR_VAL(key.s));
			} else {
				zend_hash_next_index_insert_ptr(addHash, newType);
			}
		}
		smart_str_free(&key);

		if (model != NULL) {
			sdlContentModelPtr newModel = emalloc(sizeof(sdlContentModel));

			newModel->kind = XSD_CONTENT_ELEMENT;
			newModel->u.element = newType;

			schema_min_max(element, newModel);


			zend_hash_next_index_insert_ptr(model->u.content, newModel);
		}
		cur_type = newType;
	} else {
		soap_error0(E_ERROR, "Parsing Schema: element has no 'name' nor 'ref' attributes");
	}

	/* nillable = boolean : false */
	attrs = element->properties;
	attr = get_attribute(attrs, "nillable");
	if (attr) {
		if (ref != NULL) {
			soap_error0(E_ERROR, "Parsing Schema: element has both 'ref' and 'nillable' attributes");
		}
		if (!stricmp((char*)attr->children->content, "true") ||
			!stricmp((char*)attr->children->content, "1")) {
			cur_type->nillable = TRUE;
		} else {
			cur_type->nillable = FALSE;
		}
	} else {
		cur_type->nillable = FALSE;
	}

	attr = get_attribute(attrs, "fixed");
	if (attr) {
		if (ref != NULL) {
			soap_error0(E_ERROR, "Parsing Schema: element has both 'ref' and 'fixed' attributes");
		}
		cur_type->fixed = estrdup((char*)attr->children->content);
	}

	attr = get_attribute(attrs, "default");
	if (attr) {
		if (ref != NULL) {
			soap_error0(E_ERROR, "Parsing Schema: element has both 'ref' and 'fixed' attributes");
		} else if (ref != NULL) {
			soap_error0(E_ERROR, "Parsing Schema: element has both 'default' and 'fixed' attributes");
		}
		cur_type->def = estrdup((char*)attr->children->content);
	}

	/* form */
	attr = get_attribute(attrs, "form");
	if (attr) {
		if (strncmp((char*)attr->children->content, "qualified", sizeof("qualified")) == 0) {
		  cur_type->form = XSD_FORM_QUALIFIED;
		} else if (strncmp((char*)attr->children->content, "unqualified", sizeof("unqualified")) == 0) {
		  cur_type->form = XSD_FORM_UNQUALIFIED;
		} else {
		  cur_type->form = XSD_FORM_DEFAULT;
		}
	} else {
	  cur_type->form = XSD_FORM_DEFAULT;
	}
	if (cur_type->form == XSD_FORM_DEFAULT) {
 		xmlNodePtr parent = element->parent;
 		while (parent) {
			if (node_is_equal_ex(parent, "schema", SCHEMA_NAMESPACE)) {
				xmlAttrPtr def;
				def = get_attribute(parent->properties, "elementFormDefault");
				if(def == NULL || strncmp((char*)def->children->content, "qualified", sizeof("qualified"))) {
					cur_type->form = XSD_FORM_UNQUALIFIED;
				} else {
					cur_type->form = XSD_FORM_QUALIFIED;
				}
				break;
			}
			parent = parent->parent;
  	}
		if (parent == NULL) {
			cur_type->form = XSD_FORM_UNQUALIFIED;
		}
	}

	/* type = QName */
	type = get_attribute(attrs, "type");
	if (type) {
		char *cptype, *str_ns;
		xmlNsPtr nsptr;

		if (ref != NULL) {
			soap_error0(E_ERROR, "Parsing Schema: element has both 'ref' and 'type' attributes");
		}
		parse_namespace(type->children->content, &cptype, &str_ns);
		nsptr = xmlSearchNs(element->doc, element, BAD_CAST(str_ns));
		if (nsptr != NULL) {
			cur_type->encode = get_create_encoder(sdl, cur_type, nsptr->href, BAD_CAST(cptype));
		}
		if (str_ns) {efree(str_ns);}
		if (cptype) {efree(cptype);}
	}

	trav = element->children;
	if (trav != NULL && node_is_equal(trav, "annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL) {
		if (node_is_equal(trav,"simpleType")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: element has both 'ref' attribute and subtype");
			} else if (type != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: element has both 'type' attribute and subtype");
			}
			schema_simpleType(sdl, tns, trav, cur_type);
			trav = trav->next;
		} else if (node_is_equal(trav,"complexType")) {
			if (ref != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: element has both 'ref' attribute and subtype");
			} else if (type != NULL) {
				soap_error0(E_ERROR, "Parsing Schema: element has both 'type' attribute and subtype");
			}
			schema_complexType(sdl, tns, trav, cur_type);
			trav = trav->next;
		}
	}
	while (trav != NULL) {
		if (node_is_equal(trav,"unique")) {
			/* TODO: <unique> support */
		} else if (node_is_equal(trav,"key")) {
			/* TODO: <key> support */
		} else if (node_is_equal(trav,"keyref")) {
			/* TODO: <keyref> support */
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in element", trav->name);
		}
		trav = trav->next;
	}

	return TRUE;
}