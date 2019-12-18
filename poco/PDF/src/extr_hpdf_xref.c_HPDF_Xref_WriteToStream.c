#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {int size; } ;
struct TYPE_15__ {scalar_t__ start_offset; int addr; struct TYPE_15__* prev; TYPE_12__* entries; } ;
struct TYPE_14__ {int gen_no; int byte_offset; int /*<<< orphan*/  entry_typ; int /*<<< orphan*/  obj; } ;
struct TYPE_13__ {int count; } ;
typedef  TYPE_1__* HPDF_XrefEntry ;
typedef  TYPE_2__* HPDF_Xref ;
typedef  int HPDF_UINT16 ;
typedef  int HPDF_UINT ;
typedef  TYPE_3__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_Encrypt ;

/* Variables and functions */
 scalar_t__ HPDF_BYTE_OFFSET_LEN ; 
 int /*<<< orphan*/  HPDF_Encrypt_InitKey (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ HPDF_GEN_NO_LEN ; 
 char* HPDF_IToA (char*,int,char*) ; 
 char* HPDF_IToA2 (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_List_ItemAt (TYPE_12__*,int) ; 
 scalar_t__ HPDF_OK ; 
 scalar_t__ HPDF_Obj_WriteValue (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int HPDF_SHORT_BUF_SIZ ; 
 scalar_t__ HPDF_StrCpy (char*,char*,char*) ; 
 scalar_t__ HPDF_Stream_WriteStr (TYPE_3__*,char*) ; 
 TYPE_1__* HPDF_Xref_GetEntry (TYPE_2__*,int) ; 
 scalar_t__ WriteTrailer (TYPE_2__*,TYPE_3__*) ; 

HPDF_STATUS
HPDF_Xref_WriteToStream  (HPDF_Xref    xref,
                          HPDF_Stream  stream,
                          HPDF_Encrypt e)
{
    HPDF_STATUS ret;
    HPDF_UINT i;
    char buf[HPDF_SHORT_BUF_SIZ];
    char* pbuf;
    char* eptr = buf + HPDF_SHORT_BUF_SIZ - 1;
    HPDF_UINT str_idx;
    HPDF_Xref tmp_xref = xref;

    /* write each objects of xref to the specified stream */

    HPDF_PTRACE((" HPDF_Xref_WriteToStream\n"));

    while (tmp_xref) {
        if (tmp_xref->start_offset == 0)
            str_idx = 1;
        else
            str_idx = 0;

        for (i = str_idx; i < tmp_xref->entries->count; i++) {
            HPDF_XrefEntry  entry =
                        (HPDF_XrefEntry)HPDF_List_ItemAt (tmp_xref->entries, i);
            HPDF_UINT obj_id = tmp_xref->start_offset + i;
            HPDF_UINT16 gen_no = entry->gen_no;

            entry->byte_offset = stream->size;

            pbuf = buf;
            pbuf = HPDF_IToA (pbuf, obj_id, eptr);
            *pbuf++ = ' ';
            pbuf = HPDF_IToA (pbuf, gen_no, eptr);
            HPDF_StrCpy(pbuf, " obj\012", eptr);

            if ((ret = HPDF_Stream_WriteStr (stream, buf)) != HPDF_OK)
               return ret;

            if (e)
                HPDF_Encrypt_InitKey (e, obj_id, gen_no);

            if ((ret = HPDF_Obj_WriteValue (entry->obj, stream, e)) != HPDF_OK)
                return ret;

            if ((ret = HPDF_Stream_WriteStr (stream, "\012endobj\012"))
                    != HPDF_OK)
                return ret;
       }

       tmp_xref = tmp_xref->prev;
    }

    /* start to write cross-reference table */

    tmp_xref = xref;

    while (tmp_xref) {
        tmp_xref->addr = stream->size;

        pbuf = buf;
        pbuf = (char *)HPDF_StrCpy (pbuf, "xref\012", eptr);
        pbuf = HPDF_IToA (pbuf, tmp_xref->start_offset, eptr);
        *pbuf++ = ' ';
        pbuf = HPDF_IToA (pbuf, tmp_xref->entries->count, eptr);
        HPDF_StrCpy (pbuf, "\012", eptr);
        ret = HPDF_Stream_WriteStr (stream, buf);
        if (ret != HPDF_OK)
            return ret;

        for (i = 0; i < tmp_xref->entries->count; i++) {
            HPDF_XrefEntry entry = HPDF_Xref_GetEntry(tmp_xref, i);

            pbuf = buf;
            pbuf = HPDF_IToA2 (pbuf, entry->byte_offset, HPDF_BYTE_OFFSET_LEN +
                    1);
            *pbuf++ = ' ';
            pbuf = HPDF_IToA2 (pbuf, entry->gen_no, HPDF_GEN_NO_LEN + 1);
            *pbuf++ = ' ';
            *pbuf++ = entry->entry_typ;
            HPDF_StrCpy (pbuf, "\015\012", eptr); /* Acrobat 8.15 requires both \r and \n here */
            ret = HPDF_Stream_WriteStr (stream, buf);
            if (ret != HPDF_OK)
                return ret;
        }

        tmp_xref = tmp_xref->prev;
    }

    /* write trailer dictionary */
    ret = WriteTrailer (xref, stream);

    return ret;
}