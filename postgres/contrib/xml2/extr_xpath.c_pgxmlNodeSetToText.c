#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlNodeSetPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  TYPE_2__* xmlBufferPtr ;
struct TYPE_13__ {int /*<<< orphan*/  doc; } ;
struct TYPE_12__ {int /*<<< orphan*/  content; } ;
struct TYPE_11__ {int nodeNr; TYPE_3__** nodeTab; } ;

/* Variables and functions */
 TYPE_2__* xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlBufferWriteCHAR (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlBufferWriteChar (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  xmlNodeDump (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlStrdup (int /*<<< orphan*/ ) ; 
 scalar_t__ xmlStrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmlXPathCastNodeToString (TYPE_3__*) ; 

__attribute__((used)) static xmlChar *
pgxmlNodeSetToText(xmlNodeSetPtr nodeset,
				   xmlChar *toptagname,
				   xmlChar *septagname,
				   xmlChar *plainsep)
{
	xmlBufferPtr buf;
	xmlChar    *result;
	int			i;

	buf = xmlBufferCreate();

	if ((toptagname != NULL) && (xmlStrlen(toptagname) > 0))
	{
		xmlBufferWriteChar(buf, "<");
		xmlBufferWriteCHAR(buf, toptagname);
		xmlBufferWriteChar(buf, ">");
	}
	if (nodeset != NULL)
	{
		for (i = 0; i < nodeset->nodeNr; i++)
		{
			if (plainsep != NULL)
			{
				xmlBufferWriteCHAR(buf,
								   xmlXPathCastNodeToString(nodeset->nodeTab[i]));

				/* If this isn't the last entry, write the plain sep. */
				if (i < (nodeset->nodeNr) - 1)
					xmlBufferWriteChar(buf, (char *) plainsep);
			}
			else
			{
				if ((septagname != NULL) && (xmlStrlen(septagname) > 0))
				{
					xmlBufferWriteChar(buf, "<");
					xmlBufferWriteCHAR(buf, septagname);
					xmlBufferWriteChar(buf, ">");
				}
				xmlNodeDump(buf,
							nodeset->nodeTab[i]->doc,
							nodeset->nodeTab[i],
							1, 0);

				if ((septagname != NULL) && (xmlStrlen(septagname) > 0))
				{
					xmlBufferWriteChar(buf, "</");
					xmlBufferWriteCHAR(buf, septagname);
					xmlBufferWriteChar(buf, ">");
				}
			}
		}
	}

	if ((toptagname != NULL) && (xmlStrlen(toptagname) > 0))
	{
		xmlBufferWriteChar(buf, "</");
		xmlBufferWriteCHAR(buf, toptagname);
		xmlBufferWriteChar(buf, ">");
	}
	result = xmlStrdup(buf->content);
	xmlBufferFree(buf);
	return result;
}