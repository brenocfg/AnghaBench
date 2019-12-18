#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNsPtr ;
typedef  TYPE_2__* xmlNodePtr ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_8__ {scalar_t__ type; struct TYPE_8__* parent; TYPE_1__* ns; TYPE_1__* nsDef; } ;
struct TYPE_7__ {scalar_t__ prefix; scalar_t__ href; struct TYPE_7__* next; } ;

/* Variables and functions */
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ XML_ENTITY_DECL ; 
 scalar_t__ XML_ENTITY_NODE ; 
 scalar_t__ XML_ENTITY_REF_NODE ; 
 TYPE_1__* xmlSearchNs (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 
 scalar_t__ xmlStrEqual (scalar_t__,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static xmlNsPtr xmlSearchNsPrefixByHref(xmlDocPtr doc, xmlNodePtr node, const xmlChar * href)
{
	xmlNsPtr cur;
	xmlNodePtr orig = node;

	while (node) {
		if (node->type == XML_ENTITY_REF_NODE ||
		    node->type == XML_ENTITY_NODE ||
		    node->type == XML_ENTITY_DECL) {
			return NULL;
		}
		if (node->type == XML_ELEMENT_NODE) {
			cur = node->nsDef;
			while (cur != NULL) {
				if (cur->prefix && cur->href && xmlStrEqual(cur->href, href)) {
					if (xmlSearchNs(doc, node, cur->prefix) == cur) {
						return cur;
					}
				}
				cur = cur->next;
			}
			if (orig != node) {
				cur = node->ns;
				if (cur != NULL) {
					if (cur->prefix && cur->href && xmlStrEqual(cur->href, href)) {
						if (xmlSearchNs(doc, node, cur->prefix) == cur) {
							return cur;
						}
					}
				}
			}
		}
		node = node->parent;
	}
	return NULL;
}