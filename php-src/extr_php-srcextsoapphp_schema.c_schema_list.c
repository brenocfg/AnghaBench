#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNsPtr ;
typedef  TYPE_3__* xmlNodePtr ;
typedef  TYPE_4__* xmlAttrPtr ;
typedef  TYPE_5__* sdlTypePtr ;
typedef  int /*<<< orphan*/  sdlType ;
typedef  TYPE_6__* sdlPtr ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_28__ {int /*<<< orphan*/  types; } ;
struct TYPE_27__ {char* name; int /*<<< orphan*/ * elements; void* namens; int /*<<< orphan*/  encode; } ;
struct TYPE_26__ {TYPE_1__* children; } ;
struct TYPE_25__ {int /*<<< orphan*/  name; struct TYPE_25__* next; struct TYPE_25__* children; int /*<<< orphan*/  doc; int /*<<< orphan*/  properties; } ;
struct TYPE_24__ {scalar_t__ href; } ;
struct TYPE_23__ {scalar_t__ content; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int /*<<< orphan*/  MAX_LENGTH_OF_LONG ; 
 int TRUE ; 
 int /*<<< orphan*/  delete_type ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* emalloc (int) ; 
 void* estrdup (char*) ; 
 TYPE_4__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_create_encoder (TYPE_6__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ node_is_equal (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  parse_namespace (scalar_t__,char**,char**) ; 
 int /*<<< orphan*/  schema_simpleType (TYPE_6__*,TYPE_4__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_next_index_insert_ptr (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  zend_hash_num_elements (int /*<<< orphan*/ ) ; 
 char* zend_print_long_to_buf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int schema_list(sdlPtr sdl, xmlAttrPtr tns, xmlNodePtr listType, sdlTypePtr cur_type)
{
	xmlNodePtr trav;
	xmlAttrPtr itemType;

	itemType = get_attribute(listType->properties, "itemType");
	if (itemType != NULL) {
		char *type, *ns;
		xmlNsPtr nsptr;

		parse_namespace(itemType->children->content, &type, &ns);
		nsptr = xmlSearchNs(listType->doc, listType, BAD_CAST(ns));
		if (nsptr != NULL) {
			sdlTypePtr newType;

			newType = emalloc(sizeof(sdlType));
			memset(newType, 0, sizeof(sdlType));

			newType->name = estrdup(type);
			newType->namens = estrdup((char*)nsptr->href);

			newType->encode = get_create_encoder(sdl, newType, nsptr->href, BAD_CAST(type));

			if (cur_type->elements == NULL) {
				cur_type->elements = emalloc(sizeof(HashTable));
				zend_hash_init(cur_type->elements, 0, NULL, delete_type, 0);
			}
			zend_hash_next_index_insert_ptr(cur_type->elements, newType);
		}
		if (type) {efree(type);}
		if (ns) {efree(ns);}
	}

	trav = listType->children;
	if (trav != NULL && node_is_equal(trav,"annotation")) {
		/* TODO: <annotation> support */
		trav = trav->next;
	}
	if (trav != NULL && node_is_equal(trav,"simpleType")) {
		sdlTypePtr newType;

		if (itemType != NULL) {
			soap_error0(E_ERROR, "Parsing Schema: element has both 'itemType' attribute and subtype");
		}

		newType = emalloc(sizeof(sdlType));
		memset(newType, 0, sizeof(sdlType));

		{
			char buf[MAX_LENGTH_OF_LONG + 1];
			char *res = zend_print_long_to_buf(buf + sizeof(buf) - 1, zend_hash_num_elements(sdl->types));
			char *str = emalloc(sizeof("anonymous")-1 + (buf + sizeof(buf) - res));

			memcpy(str, "anonymous", sizeof("anonymous")-1);
			memcpy(str + sizeof("anonymous")-1, res, buf + sizeof(buf) - res);
			newType->name = str;
		}
		newType->namens = estrdup((char*)tns->children->content);

		if (cur_type->elements == NULL) {
			cur_type->elements = emalloc(sizeof(HashTable));
			zend_hash_init(cur_type->elements, 0, NULL, delete_type, 0);
		}
		zend_hash_next_index_insert_ptr(cur_type->elements, newType);

		schema_simpleType(sdl, tns, trav, newType);

		trav = trav->next;
	}
	if (trav != NULL) {
		soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in list", trav->name);
	}
	return TRUE;
}