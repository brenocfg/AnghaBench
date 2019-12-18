#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ has_differences; size_t first_char; size_t last_char; int* differences; int /*<<< orphan*/ * unicode_map; int /*<<< orphan*/  base_encoding; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  size_t HPDF_INT ;
typedef  TYPE_1__* HPDF_Encoder ;
typedef  TYPE_2__* HPDF_BasicEncoderAttr ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_ENCODING_FONT_SPECIFIC ; 
 char* HPDF_IToA (char*,size_t,char*) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_StrCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_StrCpy (char*,char const*,char*) ; 
 scalar_t__ HPDF_Stream_WriteEscapeName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_WriteStr (int /*<<< orphan*/ ,char*) ; 
 int HPDF_TEXT_DEFAULT_LEN ; 
 scalar_t__ HPDF_TRUE ; 
 char* HPDF_UnicodeToGryphName (int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_BasicEncoder_Write  (HPDF_Encoder  encoder,
                          HPDF_Stream   out)
{
    HPDF_STATUS ret;
    HPDF_BasicEncoderAttr attr = (HPDF_BasicEncoderAttr)encoder->attr;

    HPDF_PTRACE ((" HPDF_BasicEncoder_Write\n"));

    /*  if HPDF_ENCODING_FONT_SPECIFIC is selected, no Encoding object will be "
     *  written.
     */
    if (HPDF_StrCmp (attr->base_encoding, HPDF_ENCODING_FONT_SPECIFIC) == 0)
        return HPDF_OK;

    /* if encoder has differences-data, encoding object is written as
       dictionary-object, otherwise it is written as name-object. */
    if (attr->has_differences == HPDF_TRUE) {
        ret = HPDF_Stream_WriteStr (out,
                "/Encoding <<\012"
                "/Type /Encoding\012"
                "/BaseEncoding ");
        if (ret != HPDF_OK)
            return ret;
    } else {
        ret = HPDF_Stream_WriteStr (out, "/Encoding ");
        if (ret != HPDF_OK)
            return ret;
    }

    ret = HPDF_Stream_WriteEscapeName (out, attr->base_encoding);
    if (ret != HPDF_OK)
        return ret;

    ret = HPDF_Stream_WriteStr (out, "\012");
    if (ret != HPDF_OK)
        return ret;

    /* write differences data */
    if (attr->has_differences == HPDF_TRUE) {
        HPDF_INT i;

        ret = HPDF_Stream_WriteStr (out, "/Differences [");
        if (ret != HPDF_OK)
            return ret;

        for (i = attr->first_char; i <= attr->last_char; i++) {
            if (attr->differences[i] == 1) {
                char tmp[HPDF_TEXT_DEFAULT_LEN];
                char* ptmp = tmp;
                const char* char_name =
                    HPDF_UnicodeToGryphName (attr->unicode_map[i]);

                ptmp = HPDF_IToA (ptmp, i, tmp + HPDF_TEXT_DEFAULT_LEN - 1);
                *ptmp++ = ' ';
                *ptmp++ = '/';
                ptmp = (char *)HPDF_StrCpy (ptmp, char_name, tmp +
                        HPDF_TEXT_DEFAULT_LEN - 1);
                *ptmp++ = ' ';
                *ptmp = 0;

                ret = HPDF_Stream_WriteStr (out, tmp);
                if (ret != HPDF_OK)
                    return ret;
            }
        }

        ret = HPDF_Stream_WriteStr (out, "]\012>>\012");
    }

    return ret;
}