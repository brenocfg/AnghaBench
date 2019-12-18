#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  unicode; void* width; void* char_cd; } ;
struct TYPE_7__ {void* top; void* right; void* bottom; void* left; } ;
struct TYPE_9__ {int base_font; scalar_t__ italic_angle; int /*<<< orphan*/  error; int /*<<< orphan*/  mmgr; void* stemv; void* stemh; void* descent; void* ascent; void* cap_height; TYPE_1__ font_bbox; int /*<<< orphan*/  flags; int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {int char_set; int encoding_scheme; int widths_count; TYPE_4__* widths; } ;
typedef  void* HPDF_UINT16 ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_2__* HPDF_Type1FontDefAttr ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  void* HPDF_REAL ;
typedef  void* HPDF_INT16 ;
typedef  TYPE_3__* HPDF_FontDef ;
typedef  TYPE_4__ HPDF_CharData ;

/* Variables and functions */
 char* GetKeyword (char const*,char*,int) ; 
 int HPDF_AToI (char const*) ; 
 int /*<<< orphan*/  HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FONT_FIXED_WIDTH ; 
 int /*<<< orphan*/  HPDF_FONT_FOURCE_BOLD ; 
 int /*<<< orphan*/  HPDF_FONT_ITALIC ; 
 int HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_GryphNameToUnicode (char*) ; 
 int HPDF_INT_LEN ; 
 int /*<<< orphan*/  HPDF_INVALID_AFM_HEADER ; 
 int /*<<< orphan*/  HPDF_INVALID_CHAR_MATRICS_DATA ; 
 int /*<<< orphan*/  HPDF_INVALID_N_DATA ; 
 int /*<<< orphan*/  HPDF_INVALID_WX_DATA ; 
 int HPDF_LIMIT_MAX_NAME_LEN ; 
 int /*<<< orphan*/  HPDF_LIMIT_MAX_STRING_LEN ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_StrCmp (char const*,char*) ; 
 int /*<<< orphan*/  HPDF_StrCpy (int,char const*,int) ; 
 scalar_t__ HPDF_StrLen (char const*,int /*<<< orphan*/ ) ; 
 char* HPDF_StrStr (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_Stream_ReadLn (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int HPDF_TMP_BUF_SIZ ; 

__attribute__((used)) static HPDF_STATUS
LoadAfm (HPDF_FontDef  fontdef,
         HPDF_Stream   stream)
{
    HPDF_Type1FontDefAttr attr = (HPDF_Type1FontDefAttr)fontdef->attr;
    char buf[HPDF_TMP_BUF_SIZ];
    HPDF_CharData* cdata;
    HPDF_STATUS ret;
    HPDF_UINT len;
    char keyword[HPDF_LIMIT_MAX_NAME_LEN + 1];
    HPDF_UINT i;

    HPDF_PTRACE ((" LoadAfm\n"));

    len = HPDF_TMP_BUF_SIZ;

    /* chaeck AFM header */
    if ((ret = HPDF_Stream_ReadLn (stream, buf, &len)) != HPDF_OK)
         return ret;

    GetKeyword (buf, keyword, HPDF_LIMIT_MAX_NAME_LEN + 1);

    if (HPDF_StrCmp (keyword, "StartFontMetrics") != 0)
        return HPDF_INVALID_AFM_HEADER;

    /* Global Font Information */

    for (;;) {
        const char *s;

        len = HPDF_TMP_BUF_SIZ;
        if ((ret = HPDF_Stream_ReadLn (stream, buf, &len)) != HPDF_OK)
            return ret;

        s = GetKeyword (buf, keyword, HPDF_LIMIT_MAX_NAME_LEN + 1);

        if (HPDF_StrCmp (keyword, "FontName") == 0) {
            HPDF_StrCpy (fontdef->base_font, s,
                    fontdef->base_font + HPDF_LIMIT_MAX_NAME_LEN);
        } else

        if (HPDF_StrCmp (keyword, "Weight") == 0) {
            if (HPDF_StrCmp (s, "Bold") == 0)
                fontdef->flags |= HPDF_FONT_FOURCE_BOLD;
        } else

        if (HPDF_StrCmp (keyword, "IsFixedPitch") == 0) {
            if (HPDF_StrCmp (s, "true") == 0)
               fontdef->flags |= HPDF_FONT_FIXED_WIDTH;
        } else

        if (HPDF_StrCmp (keyword, "ItalicAngle") == 0) {
            fontdef->italic_angle = (HPDF_INT16)HPDF_AToI (s);
            if (fontdef->italic_angle != 0)
                fontdef->flags |= HPDF_FONT_ITALIC;
        } else

        if (HPDF_StrCmp (keyword, "CharacterSet") == 0) {
            HPDF_UINT len = HPDF_StrLen (s, HPDF_LIMIT_MAX_STRING_LEN);

            if (len > 0) {
                attr->char_set = HPDF_GetMem (fontdef->mmgr, len + 1);
                if (!attr->char_set)
                    return HPDF_Error_GetCode (fontdef->error);

                HPDF_StrCpy (attr->char_set, s, attr->char_set + len);
            }
        } else
        if (HPDF_StrCmp (keyword, "FontBBox") == 0) {
            char buf[HPDF_INT_LEN + 1];

            s = GetKeyword (s, buf, HPDF_INT_LEN + 1);
            fontdef->font_bbox.left = (HPDF_REAL)HPDF_AToI (buf);

            s = GetKeyword (s, buf, HPDF_INT_LEN + 1);
            fontdef->font_bbox.bottom = (HPDF_REAL)HPDF_AToI (buf);

            s = GetKeyword (s, buf, HPDF_INT_LEN + 1);
            fontdef->font_bbox.right = (HPDF_REAL)HPDF_AToI (buf);

            GetKeyword (s, buf, HPDF_INT_LEN + 1);
            fontdef->font_bbox.top = (HPDF_REAL)HPDF_AToI (buf);
        } else
        if (HPDF_StrCmp (keyword, "EncodingScheme") == 0) {
            HPDF_StrCpy (attr->encoding_scheme, s,
                    attr->encoding_scheme + HPDF_LIMIT_MAX_NAME_LEN);
        } else
        if (HPDF_StrCmp (keyword, "CapHeight") == 0) {
            fontdef->cap_height = (HPDF_UINT16)HPDF_AToI (s);
        } else
        if (HPDF_StrCmp (keyword, "Ascender") == 0) {
            fontdef->ascent = (HPDF_INT16)HPDF_AToI (s);
        } else
        if (HPDF_StrCmp (keyword, "Descender") == 0) {
            fontdef->descent = (HPDF_INT16)HPDF_AToI (s);
        } else
        if (HPDF_StrCmp (keyword, "STDHW") == 0) {
            fontdef->stemh = (HPDF_UINT16)HPDF_AToI (s);
        } else
        if (HPDF_StrCmp (keyword, "STDHV") == 0) {
            fontdef->stemv = (HPDF_UINT16)HPDF_AToI (s);
        } else
        if (HPDF_StrCmp (keyword, "StartCharMetrics") == 0) {
            attr->widths_count = HPDF_AToI (s);
            break;
        }
    }

    cdata = (HPDF_CharData*)HPDF_GetMem (fontdef->mmgr,
            sizeof(HPDF_CharData) * attr->widths_count);
    if (cdata == NULL)
        return HPDF_Error_GetCode (fontdef->error);

    HPDF_MemSet (cdata, 0, sizeof(HPDF_CharData) * attr->widths_count);
    attr->widths = cdata;

    /* load CharMetrics */
    for (i = 0; i < attr->widths_count; i++, cdata++) {
        const char *s;
        char buf2[HPDF_LIMIT_MAX_NAME_LEN + 1];

        len = HPDF_TMP_BUF_SIZ;
        if ((ret = HPDF_Stream_ReadLn (stream, buf, &len)) != HPDF_OK)
            return ret;

        /* C default character code. */
        s = GetKeyword (buf, buf2, HPDF_LIMIT_MAX_NAME_LEN + 1);
        if (HPDF_StrCmp (buf2, "CX") == 0) {
            /* not suppoted yet. */
            return HPDF_SetError (fontdef->error,
                    HPDF_INVALID_CHAR_MATRICS_DATA, 0);
        } else
        if (HPDF_StrCmp (buf2, "C") == 0) {
            s += 2;

            s = GetKeyword (s, buf2, HPDF_LIMIT_MAX_NAME_LEN + 1);
              HPDF_AToI (buf2);

            cdata->char_cd = (HPDF_INT16)HPDF_AToI (buf2);

        } else
            return HPDF_SetError (fontdef->error,
                    HPDF_INVALID_CHAR_MATRICS_DATA, 0);

        /* WX Character width */
        s = HPDF_StrStr (s, "WX ", 0);
        if (!s)
            return HPDF_SetError (fontdef->error, HPDF_INVALID_WX_DATA, 0);

        s += 3;

        s = GetKeyword (s, buf2, HPDF_LIMIT_MAX_NAME_LEN + 1);
        if (buf2[0] == 0)
            return HPDF_SetError (fontdef->error, HPDF_INVALID_WX_DATA, 0);

        cdata->width = (HPDF_INT16)HPDF_AToI (buf2);

        /* N PostScript language character name */
        s = HPDF_StrStr (s, "N ", 0);
        if (!s)
            return HPDF_SetError (fontdef->error, HPDF_INVALID_N_DATA, 0);

        s += 2;

        GetKeyword (s, buf2, HPDF_LIMIT_MAX_NAME_LEN + 1);

        cdata->unicode = HPDF_GryphNameToUnicode (buf2);

    }

    return HPDF_OK;
}