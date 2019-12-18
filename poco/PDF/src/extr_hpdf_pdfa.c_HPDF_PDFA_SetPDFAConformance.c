#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  catalog; int /*<<< orphan*/  pdf_version; int /*<<< orphan*/  xref; int /*<<< orphan*/  mmgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  stream; } ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int HPDF_PDFAType ;
typedef  TYPE_1__* HPDF_OutputIntent ;
typedef  TYPE_2__* HPDF_Doc ;

/* Variables and functions */
 scalar_t__ ConvertDateToXMDate (int /*<<< orphan*/ ,char const*) ; 
 char const* DC_CREATOR_ENDTAG ; 
 char const* DC_CREATOR_STARTTAG ; 
 char const* DC_DESCRIPTION_ENDTAG ; 
 char const* DC_DESCRIPTION_STARTTAG ; 
 char const* DC_FOOTER ; 
 char const* DC_HEADER ; 
 char const* DC_TITLE_ENDTAG ; 
 char const* DC_TITLE_STARTTAG ; 
 char const* FOOTER ; 
 char const* HEADER ; 
 TYPE_1__* HPDF_DictStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  HPDF_Dict_AddName (TYPE_1__*,char*,char*) ; 
 scalar_t__ HPDF_GetInfoAttr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_HasDoc (TYPE_2__*) ; 
 int /*<<< orphan*/  HPDF_INFO_AUTHOR ; 
 int /*<<< orphan*/  HPDF_INFO_CREATION_DATE ; 
 int /*<<< orphan*/  HPDF_INFO_CREATOR ; 
 int /*<<< orphan*/  HPDF_INFO_KEYWORDS ; 
 int /*<<< orphan*/  HPDF_INFO_MOD_DATE ; 
 int /*<<< orphan*/  HPDF_INFO_PRODUCER ; 
 int /*<<< orphan*/  HPDF_INFO_SUBJECT ; 
 int /*<<< orphan*/  HPDF_INFO_TITLE ; 
 scalar_t__ HPDF_INVALID_DOCUMENT ; 
 scalar_t__ HPDF_INVALID_STREAM ; 
 scalar_t__ HPDF_OK ; 
#define  HPDF_PDFA_1A 129 
#define  HPDF_PDFA_1B 128 
 scalar_t__ HPDF_PDFA_GenerateID (TYPE_2__*) ; 
 scalar_t__ HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  HPDF_VER_14 ; 
 char const* PDFAID_PDFA1A ; 
 char const* PDFAID_PDFA1B ; 
 char const* PDF_FOOTER ; 
 char const* PDF_HEADER ; 
 char const* PDF_KEYWORDS_ENDTAG ; 
 char const* PDF_KEYWORDS_STARTTAG ; 
 char const* PDF_PRODUCER_ENDTAG ; 
 char const* PDF_PRODUCER_STARTTAG ; 
 char const* XMP_CREATE_DATE_ENDTAG ; 
 char const* XMP_CREATE_DATE_STARTTAG ; 
 char const* XMP_CREATORTOOL_ENDTAG ; 
 char const* XMP_CREATORTOOL_STARTTAG ; 
 char const* XMP_FOOTER ; 
 char const* XMP_HEADER ; 
 char const* XMP_MOD_DATE_ENDTAG ; 
 char const* XMP_MOD_DATE_STARTTAG ; 

HPDF_STATUS
HPDF_PDFA_SetPDFAConformance (HPDF_Doc pdf,HPDF_PDFAType pdfatype)
{
    HPDF_OutputIntent xmp;
    HPDF_STATUS ret;

    const char *dc_title       = NULL;
    const char *dc_creator     = NULL;
    const char *dc_description = NULL;

    const char *xmp_CreatorTool = NULL;
    const char *xmp_CreateDate  = NULL;
    const char *xmp_ModifyDate  = NULL;

    const char *pdf_Keywords    = NULL;
    const char *pdf_Producer    = NULL;

    const char *info = NULL;

    if (!HPDF_HasDoc(pdf)) {
      return HPDF_INVALID_DOCUMENT;
    }

    dc_title       = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_TITLE);
    dc_creator     = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_AUTHOR);
    dc_description = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_SUBJECT);

    xmp_CreateDate  = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_CREATION_DATE);
    xmp_ModifyDate  = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_MOD_DATE);
    xmp_CreatorTool = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_CREATOR);

    pdf_Keywords = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_KEYWORDS);
    pdf_Producer = (const char *)HPDF_GetInfoAttr(pdf, HPDF_INFO_PRODUCER);

    if((dc_title != NULL) || (dc_creator != NULL) || (dc_description != NULL)
       || (xmp_CreateDate != NULL) || (xmp_ModifyDate != NULL) || (xmp_CreatorTool != NULL)
       || (pdf_Keywords != NULL)) {

        xmp = HPDF_DictStream_New(pdf->mmgr,pdf->xref);
        if (!xmp) {
          return HPDF_INVALID_STREAM;
        }

        /* Update the PDF number version */
        pdf->pdf_version = HPDF_VER_14;

        HPDF_Dict_AddName(xmp,"Type","Metadata");
        HPDF_Dict_AddName(xmp,"SubType","XML");

        ret = HPDF_OK;
        ret += HPDF_Stream_WriteStr(xmp->stream, HEADER);

        /* Add the dc block */
        if((dc_title != NULL) || (dc_creator != NULL) || (dc_description != NULL)) {
            ret += HPDF_Stream_WriteStr(xmp->stream, DC_HEADER);

            if(dc_title != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, DC_TITLE_STARTTAG);
                ret += HPDF_Stream_WriteStr(xmp->stream, dc_title);
                ret += HPDF_Stream_WriteStr(xmp->stream, DC_TITLE_ENDTAG);
            }

            if(dc_creator != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, DC_CREATOR_STARTTAG);
                ret += HPDF_Stream_WriteStr(xmp->stream, dc_creator);
                ret += HPDF_Stream_WriteStr(xmp->stream, DC_CREATOR_ENDTAG);
            }

            if(dc_description != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, DC_DESCRIPTION_STARTTAG);
                ret += HPDF_Stream_WriteStr(xmp->stream, dc_description);
                ret += HPDF_Stream_WriteStr(xmp->stream, DC_DESCRIPTION_ENDTAG);
            }

            ret += HPDF_Stream_WriteStr(xmp->stream, DC_FOOTER);
        }

        /* Add the xmp block */
        if((xmp_CreateDate != NULL) || (xmp_ModifyDate != NULL) || (xmp_CreatorTool != NULL)) {
            ret += HPDF_Stream_WriteStr(xmp->stream, XMP_HEADER);

            /* Add CreateDate, ModifyDate, and CreatorTool */
            if(xmp_CreatorTool != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATORTOOL_STARTTAG);
                ret += HPDF_Stream_WriteStr(xmp->stream, xmp_CreatorTool);
                ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATORTOOL_ENDTAG);
            }

            if(xmp_CreateDate != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATE_DATE_STARTTAG);
                /* Convert date to XMP compatible format */
                ret += ConvertDateToXMDate(xmp->stream, xmp_CreateDate);
                ret += HPDF_Stream_WriteStr(xmp->stream, XMP_CREATE_DATE_ENDTAG);
            }

            if(xmp_ModifyDate != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, XMP_MOD_DATE_STARTTAG);
                ret += ConvertDateToXMDate(xmp->stream, xmp_ModifyDate);
                ret += HPDF_Stream_WriteStr(xmp->stream, XMP_MOD_DATE_ENDTAG);
            }

            ret += HPDF_Stream_WriteStr(xmp->stream, XMP_FOOTER);
        }

        /* Add the pdf block */
        if((pdf_Keywords != NULL) || (pdf_Producer != NULL)) {
            ret += HPDF_Stream_WriteStr(xmp->stream, PDF_HEADER);

            if(pdf_Keywords != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, PDF_KEYWORDS_STARTTAG);
                ret += HPDF_Stream_WriteStr(xmp->stream, pdf_Keywords);
                ret += HPDF_Stream_WriteStr(xmp->stream, PDF_KEYWORDS_ENDTAG);
            }

            if(pdf_Producer != NULL) {
                ret += HPDF_Stream_WriteStr(xmp->stream, PDF_PRODUCER_STARTTAG);
                ret += HPDF_Stream_WriteStr(xmp->stream, pdf_Producer);
                ret += HPDF_Stream_WriteStr(xmp->stream, PDF_PRODUCER_ENDTAG);
            }

            ret += HPDF_Stream_WriteStr(xmp->stream, PDF_FOOTER);
        }

        /* Add the pdfaid block */
        switch(pdfatype) {
          case HPDF_PDFA_1A:
            ret += HPDF_Stream_WriteStr(xmp->stream, PDFAID_PDFA1A);
            break;
          case HPDF_PDFA_1B:
            ret += HPDF_Stream_WriteStr(xmp->stream, PDFAID_PDFA1B);
            break;
        }

        ret += HPDF_Stream_WriteStr(xmp->stream, FOOTER);

        if (ret != HPDF_OK) {
          return HPDF_INVALID_STREAM;
        }

        if ((ret = HPDF_Dict_Add(pdf->catalog, "Metadata", xmp)) != HPDF_OK) {
          return ret;
        }

        return HPDF_PDFA_GenerateID(pdf);
    }

    return HPDF_OK;
}