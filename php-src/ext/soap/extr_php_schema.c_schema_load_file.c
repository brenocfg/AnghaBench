#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* xmlNodePtr ;
typedef  TYPE_3__* xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_4__* xmlAttrPtr ;
struct TYPE_23__ {int /*<<< orphan*/  docs; } ;
typedef  TYPE_5__ sdlCtx ;
struct TYPE_22__ {TYPE_1__* children; } ;
struct TYPE_21__ {int /*<<< orphan*/  children; } ;
struct TYPE_20__ {int /*<<< orphan*/  properties; } ;
struct TYPE_19__ {int /*<<< orphan*/  content; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_CAST (char*) ; 
 int /*<<< orphan*/  E_ERROR ; 
 TYPE_4__* get_attribute (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* get_node (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  load_schema (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sdl_restore_uri_credentials (TYPE_5__*) ; 
 int /*<<< orphan*/  sdl_set_uri_credentials (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  soap_error1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soap_error2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* soap_xmlParseFile (char*) ; 
 int /*<<< orphan*/  xmlFreeDoc (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlSetProp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlStrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlStrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_add_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_str_exists (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void schema_load_file(sdlCtx *ctx, xmlAttrPtr ns, xmlChar *location, xmlAttrPtr tns, int import) {
	if (location != NULL &&
	    !zend_hash_str_exists(&ctx->docs, (char*)location, xmlStrlen(location))) {
		xmlDocPtr doc;
		xmlNodePtr schema;
		xmlAttrPtr new_tns;

		sdl_set_uri_credentials(ctx, (char*)location);
		doc = soap_xmlParseFile((char*)location);
		sdl_restore_uri_credentials(ctx);

		if (doc == NULL) {
			soap_error1(E_ERROR, "Parsing Schema: can't import schema from '%s'", location);
		}
		schema = get_node(doc->children, "schema");
		if (schema == NULL) {
			xmlFreeDoc(doc);
			soap_error1(E_ERROR, "Parsing Schema: can't import schema from '%s'", location);
		}
		new_tns = get_attribute(schema->properties, "targetNamespace");
		if (import) {
			if (ns != NULL && (new_tns == NULL || xmlStrcmp(ns->children->content, new_tns->children->content) != 0)) {
				xmlFreeDoc(doc);
				soap_error2(E_ERROR, "Parsing Schema: can't import schema from '%s', unexpected 'targetNamespace'='%s'", location, ns->children->content);
			}
			if (ns == NULL && new_tns != NULL) {
				xmlFreeDoc(doc);
				soap_error2(E_ERROR, "Parsing Schema: can't import schema from '%s', unexpected 'targetNamespace'='%s'", location, new_tns->children->content);
			}
		} else {
			new_tns = get_attribute(schema->properties, "targetNamespace");
			if (new_tns == NULL) {
				if (tns != NULL) {
					xmlSetProp(schema, BAD_CAST("targetNamespace"), tns->children->content);
				}
			} else if (tns != NULL && xmlStrcmp(tns->children->content, new_tns->children->content) != 0) {
				xmlFreeDoc(doc);
				soap_error1(E_ERROR, "Parsing Schema: can't include schema from '%s', different 'targetNamespace'", location);
			}
		}
		zend_hash_str_add_ptr(&ctx->docs, (char*)location, xmlStrlen(location), doc);
		load_schema(ctx, schema);
	}
}