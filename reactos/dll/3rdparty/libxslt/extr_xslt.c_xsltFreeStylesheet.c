#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xsltStylesheetPtr ;
typedef  int /*<<< orphan*/  xsltStylesheet ;
struct TYPE_16__ {int /*<<< orphan*/  dict; int /*<<< orphan*/ * doc; int /*<<< orphan*/ * principalData; struct TYPE_16__* principal; int /*<<< orphan*/ * imports; scalar_t__ attVTs; struct TYPE_16__* mediaType; struct TYPE_16__* doctypeSystem; struct TYPE_16__* doctypePublic; struct TYPE_16__* encoding; struct TYPE_16__* version; struct TYPE_16__* methodURI; struct TYPE_16__* method; struct TYPE_16__* exclPrefixTab; int /*<<< orphan*/ * nsHash; int /*<<< orphan*/ * stripSpaces; int /*<<< orphan*/ * cdataSection; int /*<<< orphan*/ * variables; int /*<<< orphan*/  templates; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSLT_GET_INTERNAL_NSMAP (TYPE_1__*) ; 
 scalar_t__ XSLT_HAS_INTERNAL_NSMAP (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  xmlDictFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlDocGetRootElement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHashFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltCleanupStylesheetTree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltFreeAVTList (scalar_t__) ; 
 int /*<<< orphan*/  xsltFreeAttributeSetsHashes (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeDecimalFormatList (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeExts (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeKeys (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeNamespaceAliasHashes (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreePrincipalStylesheetData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeStackElemList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeStyleDocuments (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeStylePreComps (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeStylesheetList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltFreeTemplateHashes (TYPE_1__*) ; 
 int /*<<< orphan*/  xsltFreeTemplateList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsltGenericDebug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsltGenericDebugContext ; 
 int /*<<< orphan*/  xsltRestoreDocumentNamespaces (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsltShutdownExts (TYPE_1__*) ; 

void
xsltFreeStylesheet(xsltStylesheetPtr style)
{
    if (style == NULL)
        return;

#ifdef XSLT_REFACTORED
    /*
    * Start with a cleanup of the main stylesheet's doc.
    */
    if ((style->principal == style) && (style->doc))
	xsltCleanupStylesheetTree(style->doc,
	    xmlDocGetRootElement(style->doc));
#ifdef XSLT_REFACTORED_XSLT_NSCOMP
    /*
    * Restore changed ns-decls before freeing the document.
    */
    if ((style->doc != NULL) &&
	XSLT_HAS_INTERNAL_NSMAP(style))
    {
	xsltRestoreDocumentNamespaces(XSLT_GET_INTERNAL_NSMAP(style),
	    style->doc);
    }
#endif /* XSLT_REFACTORED_XSLT_NSCOMP */
#else
    /*
    * Start with a cleanup of the main stylesheet's doc.
    */
    if ((style->parent == NULL) && (style->doc))
	xsltCleanupStylesheetTree(style->doc,
	    xmlDocGetRootElement(style->doc));
#endif /* XSLT_REFACTORED */

    xsltFreeKeys(style);
    xsltFreeExts(style);
    xsltFreeTemplateHashes(style);
    xsltFreeDecimalFormatList(style);
    xsltFreeTemplateList(style->templates);
    xsltFreeAttributeSetsHashes(style);
    xsltFreeNamespaceAliasHashes(style);
    xsltFreeStylePreComps(style);
    /*
    * Free documents of all included stylsheet modules of this
    * stylesheet level.
    */
    xsltFreeStyleDocuments(style);
    /*
    * TODO: Best time to shutdown extension stuff?
    */
    xsltShutdownExts(style);

    if (style->variables != NULL)
        xsltFreeStackElemList(style->variables);
    if (style->cdataSection != NULL)
        xmlHashFree(style->cdataSection, NULL);
    if (style->stripSpaces != NULL)
        xmlHashFree(style->stripSpaces, NULL);
    if (style->nsHash != NULL)
        xmlHashFree(style->nsHash, NULL);
    if (style->exclPrefixTab != NULL)
        xmlFree(style->exclPrefixTab);
    if (style->method != NULL)
        xmlFree(style->method);
    if (style->methodURI != NULL)
        xmlFree(style->methodURI);
    if (style->version != NULL)
        xmlFree(style->version);
    if (style->encoding != NULL)
        xmlFree(style->encoding);
    if (style->doctypePublic != NULL)
        xmlFree(style->doctypePublic);
    if (style->doctypeSystem != NULL)
        xmlFree(style->doctypeSystem);
    if (style->mediaType != NULL)
        xmlFree(style->mediaType);
    if (style->attVTs)
        xsltFreeAVTList(style->attVTs);
    if (style->imports != NULL)
        xsltFreeStylesheetList(style->imports);

#ifdef XSLT_REFACTORED
    /*
    * If this is the principal stylesheet, then
    * free its internal data.
    */
    if (style->principal == style) {
	if (style->principalData) {
	    xsltFreePrincipalStylesheetData(style->principalData);
	    style->principalData = NULL;
	}
    }
#endif
    /*
    * Better to free the main document of this stylesheet level
    * at the end - so here.
    */
    if (style->doc != NULL) {
        xmlFreeDoc(style->doc);
    }

#ifdef WITH_XSLT_DEBUG
    xsltGenericDebug(xsltGenericDebugContext,
                     "freeing dictionary from stylesheet\n");
#endif
    xmlDictFree(style->dict);

    memset(style, -1, sizeof(xsltStylesheet));
    xmlFree(style);
}