#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; } ;
struct TYPE_7__ {int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {scalar_t__ length1; scalar_t__ length2; scalar_t__ length3; TYPE_4__* font_data; } ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_Type1FontDefAttr ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  TYPE_2__* HPDF_FontDef ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* HPDF_MemStream_New (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int HPDF_STREAM_BUF_SIZ ; 
 scalar_t__ HPDF_STREAM_EOF ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* HPDF_StrStr (char*,char*,int) ; 
 scalar_t__ HPDF_Stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ HPDF_Stream_Write (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_TRUE ; 
 int /*<<< orphan*/  HPDF_UNSUPPORTED_TYPE1_FONT ; 

__attribute__((used)) static HPDF_STATUS
LoadFontData (HPDF_FontDef  fontdef,
              HPDF_Stream   stream)
{
    HPDF_Type1FontDefAttr attr = (HPDF_Type1FontDefAttr)fontdef->attr;
    char buf[HPDF_STREAM_BUF_SIZ];
    char* pbuf = buf;
    HPDF_UINT len = 0;
    HPDF_STATUS ret;
    HPDF_BOOL end_flg = HPDF_FALSE;

    HPDF_PTRACE ((" LoadFontData\n"));

    attr->font_data = HPDF_MemStream_New (fontdef->mmgr, HPDF_STREAM_BUF_SIZ);

    if (!attr->font_data)
        return HPDF_Error_GetCode (fontdef->error);

    len = 11;
    ret = HPDF_Stream_Read (stream, (HPDF_BYTE *)pbuf, &len);
    if (ret != HPDF_OK)
        return ret;
    pbuf += 11;

    for (;;) {
        len = HPDF_STREAM_BUF_SIZ - 11;
        ret = HPDF_Stream_Read (stream, (HPDF_BYTE *)pbuf, &len);
        if (ret == HPDF_STREAM_EOF) {
            end_flg = HPDF_TRUE;
        } else if (ret != HPDF_OK)
            return ret;

        if (len > 0) {
            if (attr->length1 == 0) {
               const char *s1 = HPDF_StrStr (buf, "eexec", len + 11);

               /* length1 indicate the size of ascii-data of font-file. */
               if (s1)
                  attr->length1 = attr->font_data->size + (s1 - buf) + 6;
            }

            if (attr->length1 > 0 && attr->length2 == 0) {
                const char *s2 = HPDF_StrStr (buf, "cleartomark",
                        len + 11);

                if (s2)
                    attr->length2 = attr->font_data->size + - 520 -
                        attr->length1 + (s2 - buf);
                /*  length1 indicate the size of binary-data.
                 *  in most fonts, it is all right at 520 bytes . but it need
                 *  to modify because it does not fully satisfy the
                 *  specification of type-1 font.
                 */
            }
        }

        if (end_flg) {
            if ((ret = HPDF_Stream_Write (attr->font_data, (HPDF_BYTE *)buf, len + 11)) !=
                        HPDF_OK)
                return ret;

            break;
        } else {
            if ((ret = HPDF_Stream_Write (attr->font_data, (HPDF_BYTE *)buf, len)) !=
                        HPDF_OK)
                return ret;
            HPDF_MemCpy ((HPDF_BYTE *)buf, (HPDF_BYTE *)buf + len, 11);
            pbuf = buf + 11;
        }
    }

    if (attr->length1 == 0 || attr->length2 == 0)
        return HPDF_SetError (fontdef->error, HPDF_UNSUPPORTED_TYPE1_FONT, 0);

    attr->length3 = attr->font_data->size - attr->length1 - attr->length2;

    return HPDF_OK;
}