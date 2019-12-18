#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_3__* xmlAttrPtr ;
struct TYPE_41__ {TYPE_10__* sdl; void* attributeGroups; void* attributes; } ;
typedef  TYPE_4__ sdlCtx ;
struct TYPE_42__ {int /*<<< orphan*/ * URL; } ;
struct TYPE_40__ {TYPE_1__* children; } ;
struct TYPE_39__ {struct TYPE_39__* next; int /*<<< orphan*/  name; TYPE_7__* doc; int /*<<< orphan*/  properties; struct TYPE_39__* children; } ;
struct TYPE_38__ {int /*<<< orphan*/  content; } ;
struct TYPE_37__ {void* types; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  delete_attribute ; 
 int /*<<< orphan*/  delete_type ; 
 void* emalloc (int) ; 
 TYPE_3__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ node_is_equal (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  schema_attribute (TYPE_10__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_attributeGroup (TYPE_10__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  schema_complexType (TYPE_10__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_element (TYPE_10__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_group (TYPE_10__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schema_load_file (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  schema_simpleType (TYPE_10__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soap_error0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlBuildURI (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlNewNs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlNodeGetBase (TYPE_7__*,TYPE_2__*) ; 
 TYPE_3__* xmlSetProp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlStrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int load_schema(sdlCtx *ctx, xmlNodePtr schema)
{
	xmlNodePtr trav;
	xmlAttrPtr tns;

	if (!ctx->sdl->types) {
		ctx->sdl->types = emalloc(sizeof(HashTable));
		zend_hash_init(ctx->sdl->types, 0, NULL, delete_type, 0);
	}
	if (!ctx->attributes) {
		ctx->attributes = emalloc(sizeof(HashTable));
		zend_hash_init(ctx->attributes, 0, NULL, delete_attribute, 0);
	}
	if (!ctx->attributeGroups) {
		ctx->attributeGroups = emalloc(sizeof(HashTable));
		zend_hash_init(ctx->attributeGroups, 0, NULL, delete_type, 0);
	}

	tns = get_attribute(schema->properties, "targetNamespace");
	if (tns == NULL) {
		tns = xmlSetProp(schema, BAD_CAST("targetNamespace"), BAD_CAST(""));
		xmlNewNs(schema, BAD_CAST(""), NULL);
	}

	trav = schema->children;
	while (trav != NULL) {
		if (node_is_equal(trav,"include")) {
			xmlAttrPtr location;

			location = get_attribute(trav->properties, "schemaLocation");
			if (location == NULL) {
				soap_error0(E_ERROR, "Parsing Schema: include has no 'schemaLocation' attribute");
			} else {
				xmlChar *uri;
				xmlChar *base = xmlNodeGetBase(trav->doc, trav);

				if (base == NULL) {
			    uri = xmlBuildURI(location->children->content, trav->doc->URL);
				} else {
	    		uri = xmlBuildURI(location->children->content, base);
			    xmlFree(base);
				}
				schema_load_file(ctx, NULL, uri, tns, 0);
				xmlFree(uri);
			}

		} else if (node_is_equal(trav,"redefine")) {
			xmlAttrPtr location;

			location = get_attribute(trav->properties, "schemaLocation");
			if (location == NULL) {
				soap_error0(E_ERROR, "Parsing Schema: redefine has no 'schemaLocation' attribute");
			} else {
			  xmlChar *uri;
				xmlChar *base = xmlNodeGetBase(trav->doc, trav);

				if (base == NULL) {
			    uri = xmlBuildURI(location->children->content, trav->doc->URL);
				} else {
	    		uri = xmlBuildURI(location->children->content, base);
			    xmlFree(base);
				}
				schema_load_file(ctx, NULL, uri, tns, 0);
				xmlFree(uri);
				/* TODO: <redefine> support */
			}

		} else if (node_is_equal(trav,"import")) {
			xmlAttrPtr ns, location;
			xmlChar *uri = NULL;

			ns = get_attribute(trav->properties, "namespace");
			location = get_attribute(trav->properties, "schemaLocation");

			if (ns != NULL && tns != NULL && xmlStrcmp(ns->children->content, tns->children->content) == 0) {
				if (location) {
					soap_error1(E_ERROR, "Parsing Schema: can't import schema from '%s', namespace must not match the enclosing schema 'targetNamespace'", location->children->content);
				} else {
					soap_error0(E_ERROR, "Parsing Schema: can't import schema. Namespace must not match the enclosing schema 'targetNamespace'");
				}
			}
			if (location) {
				xmlChar *base = xmlNodeGetBase(trav->doc, trav);

				if (base == NULL) {
			    uri = xmlBuildURI(location->children->content, trav->doc->URL);
				} else {
	    		uri = xmlBuildURI(location->children->content, base);
			    xmlFree(base);
				}
			}
			schema_load_file(ctx, ns, uri, tns, 1);
			if (uri != NULL) {xmlFree(uri);}
		} else if (node_is_equal(trav,"annotation")) {
			/* TODO: <annotation> support */
/* annotation cleanup
			xmlNodePtr tmp = trav;
			trav = trav->next;
			xmlUnlinkNode(tmp);
			xmlFreeNode(tmp);
			continue;
*/
		} else {
			break;
		}
		trav = trav->next;
	}

	while (trav != NULL) {
		if (node_is_equal(trav,"simpleType")) {
			schema_simpleType(ctx->sdl, tns, trav, NULL);
		} else if (node_is_equal(trav,"complexType")) {
			schema_complexType(ctx->sdl, tns, trav, NULL);
		} else if (node_is_equal(trav,"group")) {
			schema_group(ctx->sdl, tns, trav, NULL, NULL);
		} else if (node_is_equal(trav,"attributeGroup")) {
			schema_attributeGroup(ctx->sdl, tns, trav, NULL, ctx);
		} else if (node_is_equal(trav,"element")) {
			schema_element(ctx->sdl, tns, trav, NULL, NULL);
		} else if (node_is_equal(trav,"attribute")) {
			schema_attribute(ctx->sdl, tns, trav, NULL, ctx);
		} else if (node_is_equal(trav,"notation")) {
			/* TODO: <notation> support */
		} else if (node_is_equal(trav,"annotation")) {
			/* TODO: <annotation> support */
		} else {
			soap_error1(E_ERROR, "Parsing Schema: unexpected <%s> in schema", trav->name);
		}
		trav = trav->next;
	}
	return TRUE;
}