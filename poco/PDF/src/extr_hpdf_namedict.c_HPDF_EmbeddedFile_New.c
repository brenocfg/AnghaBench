#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  filter; scalar_t__ stream; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  TYPE_1__* HPDF_String ;
typedef  scalar_t__ HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  TYPE_1__* HPDF_EmbeddedFile ;
typedef  TYPE_1__* HPDF_Dict ;

/* Variables and functions */
 TYPE_1__* HPDF_DictStream_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Dict_Add (TYPE_1__*,char*,TYPE_1__*) ; 
 scalar_t__ HPDF_Dict_AddName (TYPE_1__*,char*,char*) ; 
 TYPE_1__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_FileReader_New (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_STREAM_FILTER_FLATE_DECODE ; 
 int /*<<< orphan*/  HPDF_Stream_Free (scalar_t__) ; 
 TYPE_1__* HPDF_String_New (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_1__*) ; 

HPDF_EmbeddedFile
HPDF_EmbeddedFile_New  (HPDF_MMgr  mmgr,
                        HPDF_Xref  xref,
                        const char *file)
{
    HPDF_STATUS ret = HPDF_OK;
    HPDF_Dict ef;               /* the dictionary for the embedded file: /Type /EF */
    HPDF_String name;           /* the name of the file: /F (name) */
    HPDF_Dict eff;              /* ef has an /EF <<blah>> key - this is it */
    HPDF_Dict filestream;       /* the stream that /EF <</F _ _ R>> refers to */
    HPDF_Stream stream;

    ef = HPDF_Dict_New (mmgr);
    if (!ef)
        return NULL;
    if (HPDF_Xref_Add (xref, ef) != HPDF_OK)
        return NULL;

    filestream = HPDF_DictStream_New (mmgr, xref);
    if (!filestream)
        return NULL;
    stream = HPDF_FileReader_New (mmgr, file);
    if (!stream)
        return NULL;
    HPDF_Stream_Free(filestream->stream);
    filestream->stream = stream;
    filestream->filter = HPDF_STREAM_FILTER_FLATE_DECODE;

    eff = HPDF_Dict_New (mmgr);
    if (!eff)
        return NULL;

    name = HPDF_String_New (mmgr, file, NULL);
    if (!name)
        return NULL;

    ret += HPDF_Dict_AddName (ef, "Type", "F");
    ret += HPDF_Dict_Add (ef, "F", name);
    ret += HPDF_Dict_Add (ef, "EF", eff);
    ret += HPDF_Dict_Add (eff, "F", filestream);

    if (ret != HPDF_OK)
        return NULL;

    return ef;
}