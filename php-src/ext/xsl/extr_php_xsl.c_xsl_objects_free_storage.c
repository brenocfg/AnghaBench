#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
typedef  TYPE_1__* xsltStylesheetPtr ;
struct TYPE_6__ {scalar_t__ profiling; int /*<<< orphan*/ * ptr; scalar_t__ doc; scalar_t__ node_list; scalar_t__ registered_phpfunctions; scalar_t__ parameter; int /*<<< orphan*/  std; } ;
typedef  TYPE_2__ xsl_object ;
struct TYPE_5__ {int /*<<< orphan*/ * _private; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_HASHTABLE (scalar_t__) ; 
 int /*<<< orphan*/  efree (scalar_t__) ; 
 int /*<<< orphan*/  php_libxml_decrement_doc_ref (scalar_t__) ; 
 TYPE_2__* php_xsl_fetch_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeStylesheet (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 

void xsl_objects_free_storage(zend_object *object)
{
	xsl_object *intern = php_xsl_fetch_object(object);

	zend_object_std_dtor(&intern->std);

	zend_hash_destroy(intern->parameter);
	FREE_HASHTABLE(intern->parameter);

	zend_hash_destroy(intern->registered_phpfunctions);
	FREE_HASHTABLE(intern->registered_phpfunctions);

	if (intern->node_list) {
		zend_hash_destroy(intern->node_list);
		FREE_HASHTABLE(intern->node_list);
	}

	if (intern->doc) {
		php_libxml_decrement_doc_ref(intern->doc);
		efree(intern->doc);
	}

	if (intern->ptr) {
		/* free wrapper */
		if (((xsltStylesheetPtr) intern->ptr)->_private != NULL) {
			((xsltStylesheetPtr) intern->ptr)->_private = NULL;
		}

		xsltFreeStylesheet((xsltStylesheetPtr) intern->ptr);
		intern->ptr = NULL;
	}
	if (intern->profiling) {
		efree(intern->profiling);
	}
}