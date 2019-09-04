#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  TYPE_3__* xmlDocPtr ;
struct TYPE_11__ {int /*<<< orphan*/ * URL; } ;
struct TYPE_10__ {TYPE_3__* myDoc; int /*<<< orphan*/ * directory; scalar_t__ wellFormed; int /*<<< orphan*/  options; TYPE_1__* sax; } ;
struct TYPE_9__ {int /*<<< orphan*/ * error; int /*<<< orphan*/ * warning; int /*<<< orphan*/  comment; int /*<<< orphan*/  ignorableWhitespace; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_PARSE_HUGE ; 
 int php_libxml_disable_entity_loader (int) ; 
 int /*<<< orphan*/  soap_Comment ; 
 int /*<<< orphan*/  soap_ignorableWhitespace ; 
 int /*<<< orphan*/ * xmlCharStrdup (int /*<<< orphan*/ *) ; 
 TYPE_2__* xmlCreateMemoryParserCtxt (void const*,size_t) ; 
 int /*<<< orphan*/  xmlFreeDoc (TYPE_3__*) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlParseDocument (TYPE_2__*) ; 

xmlDocPtr soap_xmlParseMemory(const void *buf, size_t buf_size)
{
	xmlParserCtxtPtr ctxt = NULL;
	xmlDocPtr ret;


/*
	xmlInitParser();
*/
	ctxt = xmlCreateMemoryParserCtxt(buf, buf_size);
	if (ctxt) {
		zend_bool old;

		ctxt->sax->ignorableWhitespace = soap_ignorableWhitespace;
		ctxt->sax->comment = soap_Comment;
		ctxt->sax->warning = NULL;
		ctxt->sax->error = NULL;
		/*ctxt->sax->fatalError = NULL;*/
		ctxt->options |= XML_PARSE_HUGE;
		old = php_libxml_disable_entity_loader(1);
		xmlParseDocument(ctxt);
		php_libxml_disable_entity_loader(old);
		if (ctxt->wellFormed) {
			ret = ctxt->myDoc;
			if (ret->URL == NULL && ctxt->directory != NULL) {
				ret->URL = xmlCharStrdup(ctxt->directory);
			}
		} else {
			ret = NULL;
			xmlFreeDoc(ctxt->myDoc);
			ctxt->myDoc = NULL;
		}
		xmlFreeParserCtxt(ctxt);
	} else {
		ret = NULL;
	}

/*
	xmlCleanupParser();
*/

/*
	if (ret) {
		cleanup_xml_node((xmlNodePtr)ret);
	}
*/
	return ret;
}