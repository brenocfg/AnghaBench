#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  xmlDocPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  soapHeader ;
typedef  int /*<<< orphan*/  sdlFunctionPtr ;
typedef  int /*<<< orphan*/  cont_len ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/ * PG (int /*<<< orphan*/ ) ; 
 int SOAP_1_2 ; 
 int SOAP_GLOBAL (int) ; 
 size_t TRACK_VARS_SERVER ; 
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_globals ; 
 int /*<<< orphan*/  php_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sapi_add_header (char*,int,int) ; 
 int /*<<< orphan*/  serialize_response_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xmlDocDumpMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_clear_exception () ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zend_ini_long (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_is_auto_global_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soap_server_fault_ex(sdlFunctionPtr function, zval* fault, soapHeader *hdr) /* {{{ */
{
	int soap_version;
	xmlChar *buf;
	char cont_len[30];
	int size;
	xmlDocPtr doc_return;
	zval *agent_name;
	int use_http_error_status = 1;

	soap_version = SOAP_GLOBAL(soap_version);

	doc_return = serialize_response_call(function, NULL, NULL, fault, hdr, soap_version);

	xmlDocDumpMemory(doc_return, &buf, &size);

	if ((Z_TYPE(PG(http_globals)[TRACK_VARS_SERVER]) == IS_ARRAY || zend_is_auto_global_str(ZEND_STRL("_SERVER"))) &&
		(agent_name = zend_hash_str_find(Z_ARRVAL(PG(http_globals)[TRACK_VARS_SERVER]), "HTTP_USER_AGENT", sizeof("HTTP_USER_AGENT")-1)) != NULL &&
		Z_TYPE_P(agent_name) == IS_STRING) {
		if (strncmp(Z_STRVAL_P(agent_name), "Shockwave Flash", sizeof("Shockwave Flash")-1) == 0) {
			use_http_error_status = 0;
		}
	}
	/*
	   Want to return HTTP 500 but apache wants to over write
	   our fault code with their own handling... Figure this out later
	*/
	if (use_http_error_status) {
		sapi_add_header("HTTP/1.1 500 Internal Service Error", sizeof("HTTP/1.1 500 Internal Service Error")-1, 1);
	}
	if (zend_ini_long("zlib.output_compression", sizeof("zlib.output_compression"), 0)) {
		sapi_add_header("Connection: close", sizeof("Connection: close")-1, 1);
	} else {
		snprintf(cont_len, sizeof(cont_len), "Content-Length: %d", size);
		sapi_add_header(cont_len, strlen(cont_len), 1);
	}
	if (soap_version == SOAP_1_2) {
		sapi_add_header("Content-Type: application/soap+xml; charset=utf-8", sizeof("Content-Type: application/soap+xml; charset=utf-8")-1, 1);
	} else {
		sapi_add_header("Content-Type: text/xml; charset=utf-8", sizeof("Content-Type: text/xml; charset=utf-8")-1, 1);
	}

	php_write(buf, size);

	xmlFreeDoc(doc_return);
	xmlFree(buf);
	zend_clear_exception();
}