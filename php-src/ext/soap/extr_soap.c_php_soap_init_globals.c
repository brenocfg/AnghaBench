#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ref_map; int /*<<< orphan*/ * mem_cache; int /*<<< orphan*/  soap_version; int /*<<< orphan*/ * sdl; int /*<<< orphan*/  error_object; int /*<<< orphan*/ * error_code; scalar_t__ use_soap_error_handler; int /*<<< orphan*/ * typemap; int /*<<< orphan*/  defEncNs; int /*<<< orphan*/  defEncIndex; int /*<<< orphan*/  defEnc; } ;
typedef  TYPE_1__ zend_soap_globals ;

/* Variables and functions */
 int /*<<< orphan*/  SOAP_1_1 ; 
 int /*<<< orphan*/  ZEND_TSRMLS_CACHE_UPDATE () ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defEnc ; 
 int /*<<< orphan*/  defEncIndex ; 
 int /*<<< orphan*/  defEncNs ; 

__attribute__((used)) static void php_soap_init_globals(zend_soap_globals *soap_globals)
{
#if defined(COMPILE_DL_SOAP) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	soap_globals->defEnc = defEnc;
	soap_globals->defEncIndex = defEncIndex;
	soap_globals->defEncNs = defEncNs;
	soap_globals->typemap = NULL;
	soap_globals->use_soap_error_handler = 0;
	soap_globals->error_code = NULL;
	ZVAL_OBJ(&soap_globals->error_object, NULL);
	soap_globals->sdl = NULL;
	soap_globals->soap_version = SOAP_1_1;
	soap_globals->mem_cache = NULL;
	soap_globals->ref_map = NULL;
}