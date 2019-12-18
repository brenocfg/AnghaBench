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
typedef  int /*<<< orphan*/  buf ;
typedef  TYPE_1__* XML_ELEM_ERROR ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_ERROR_CODE ;
struct TYPE_3__ {int parser_code; int /*<<< orphan*/  byte_index; int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/ * XMLRPC_UtilityCreateFault (int /*<<< orphan*/ ,char*) ; 
#define  XML_ERROR_INCORRECT_ENCODING 129 
#define  XML_ERROR_UNKNOWN_ENCODING 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlrpc_error_parse_bad_encoding ; 
 int /*<<< orphan*/  xmlrpc_error_parse_unknown_encoding ; 
 int /*<<< orphan*/  xmlrpc_error_parse_xml_syntax ; 

__attribute__((used)) static XMLRPC_VALUE map_expat_errors(XML_ELEM_ERROR error) {
   XMLRPC_VALUE xReturn = NULL;
   if(error) {
      XMLRPC_ERROR_CODE code;
      char buf[1024];
      snprintf(buf, sizeof(buf),
               "error occurred at line %ld, column %ld, byte index %ld",
					 error->line, error->column, error->byte_index);

      /* expat specific errors */
      switch(error->parser_code) {
      case XML_ERROR_UNKNOWN_ENCODING:
         code = xmlrpc_error_parse_unknown_encoding;
         break;
      case XML_ERROR_INCORRECT_ENCODING:
         code = xmlrpc_error_parse_bad_encoding;
         break;
      default:
         code = xmlrpc_error_parse_xml_syntax;
         break;
      }
      xReturn = XMLRPC_UtilityCreateFault(code, buf);
   }
   return xReturn;
}