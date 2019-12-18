#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * res; TYPE_2__* ctxt; int /*<<< orphan*/ * doctree; } ;
typedef  TYPE_1__ xpath_workspace ;
typedef  int /*<<< orphan*/ * xmlXPathObjectPtr ;
typedef  int /*<<< orphan*/ * xmlXPathCompExprPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  PgXmlErrorContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PG_XML_STRICTNESS_LEGACY ; 
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_workspace (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_xml_done (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pgxml_parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlDocGetRootElement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlParseMemory (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlXPathCompile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlXPathCompiledEval (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  xmlXPathFreeCompExpr (int /*<<< orphan*/ *) ; 
 TYPE_2__* xmlXPathNewContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_ereport (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static xmlXPathObjectPtr
pgxml_xpath(text *document, xmlChar *xpath, xpath_workspace *workspace)
{
	int32		docsize = VARSIZE_ANY_EXHDR(document);
	PgXmlErrorContext *xmlerrcxt;
	xmlXPathCompExprPtr comppath;

	workspace->doctree = NULL;
	workspace->ctxt = NULL;
	workspace->res = NULL;

	xmlerrcxt = pgxml_parser_init(PG_XML_STRICTNESS_LEGACY);

	PG_TRY();
	{
		workspace->doctree = xmlParseMemory((char *) VARDATA_ANY(document),
											docsize);
		if (workspace->doctree != NULL)
		{
			workspace->ctxt = xmlXPathNewContext(workspace->doctree);
			workspace->ctxt->node = xmlDocGetRootElement(workspace->doctree);

			/* compile the path */
			comppath = xmlXPathCompile(xpath);
			if (comppath == NULL)
				xml_ereport(xmlerrcxt, ERROR, ERRCODE_EXTERNAL_ROUTINE_EXCEPTION,
							"XPath Syntax Error");

			/* Now evaluate the path expression. */
			workspace->res = xmlXPathCompiledEval(comppath, workspace->ctxt);

			xmlXPathFreeCompExpr(comppath);
		}
	}
	PG_CATCH();
	{
		cleanup_workspace(workspace);

		pg_xml_done(xmlerrcxt, true);

		PG_RE_THROW();
	}
	PG_END_TRY();

	if (workspace->res == NULL)
		cleanup_workspace(workspace);

	pg_xml_done(xmlerrcxt, false);

	return workspace->res;
}