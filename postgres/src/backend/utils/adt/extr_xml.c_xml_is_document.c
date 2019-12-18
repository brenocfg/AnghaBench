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
typedef  int /*<<< orphan*/  xmltype ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {scalar_t__ sqlerrcode; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 TYPE_1__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ ERRCODE_INVALID_XML_DOCUMENT ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  GetDatabaseEncoding () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_XML_SUPPORT () ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  XMLOPTION_DOCUMENT ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/ * xml_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool
xml_is_document(xmltype *arg)
{
#ifdef USE_LIBXML
	bool		result;
	volatile xmlDocPtr doc = NULL;
	MemoryContext ccxt = CurrentMemoryContext;

	/* We want to catch ereport(INVALID_XML_DOCUMENT) and return false */
	PG_TRY();
	{
		doc = xml_parse((text *) arg, XMLOPTION_DOCUMENT, true,
						GetDatabaseEncoding());
		result = true;
	}
	PG_CATCH();
	{
		ErrorData  *errdata;
		MemoryContext ecxt;

		ecxt = MemoryContextSwitchTo(ccxt);
		errdata = CopyErrorData();
		if (errdata->sqlerrcode == ERRCODE_INVALID_XML_DOCUMENT)
		{
			FlushErrorState();
			result = false;
		}
		else
		{
			MemoryContextSwitchTo(ecxt);
			PG_RE_THROW();
		}
	}
	PG_END_TRY();

	if (doc)
		xmlFreeDoc(doc);

	return result;
#else							/* not USE_LIBXML */
	NO_XML_SUPPORT();
	return false;
#endif							/* not USE_LIBXML */
}