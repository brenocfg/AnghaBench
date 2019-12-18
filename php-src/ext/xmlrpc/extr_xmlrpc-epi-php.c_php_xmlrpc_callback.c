#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {int php_executed; int /*<<< orphan*/  return_data; int /*<<< orphan*/  php_function; int /*<<< orphan*/  caller_params; int /*<<< orphan*/  xmlrpc_method; TYPE_1__* server; } ;
typedef  TYPE_2__ xmlrpc_callback_data ;
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;
struct TYPE_3__ {int /*<<< orphan*/  method_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_to_XMLRPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_RequestGetData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_RequestGetMethodName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_to_PHP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static XMLRPC_VALUE php_xmlrpc_callback(XMLRPC_SERVER server, XMLRPC_REQUEST xRequest, void* data) /* {{{ */
{
	xmlrpc_callback_data* pData = (xmlrpc_callback_data*)data;
	zval* php_function;
	zval xmlrpc_params;
	zval callback_params[3];

	zval_ptr_dtor(&pData->xmlrpc_method);
	zval_ptr_dtor(&pData->return_data);

	/* convert xmlrpc to native php types */
	ZVAL_STRING(&pData->xmlrpc_method, XMLRPC_RequestGetMethodName(xRequest));
	XMLRPC_to_PHP(XMLRPC_RequestGetData(xRequest), &xmlrpc_params);

	/* check if the called method has been previous registered */
	if ((php_function = zend_hash_find(Z_ARRVAL(pData->server->method_map), Z_STR(pData->xmlrpc_method))) != NULL) {
		ZVAL_COPY_VALUE(&pData->php_function, php_function);
	}

	/* setup data hoojum */
	ZVAL_COPY_VALUE(&callback_params[0], &pData->xmlrpc_method);
	ZVAL_COPY_VALUE(&callback_params[1], &xmlrpc_params);
	ZVAL_COPY_VALUE(&callback_params[2], &pData->caller_params);

	/* Use same C function for all methods */

	/* php func prototype: function user_func($method_name, $xmlrpc_params, $user_params) */
	call_user_function(NULL, NULL, &pData->php_function, &pData->return_data, 3, callback_params);

	pData->php_executed = 1;

	zval_ptr_dtor(&xmlrpc_params);

	return PHP_to_XMLRPC(&pData->return_data);
}