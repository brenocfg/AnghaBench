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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * encoder; scalar_t__* value; } ;
typedef  int /*<<< orphan*/  HPDF_UNICODE ;
typedef  scalar_t__ HPDF_UINT16 ;
typedef  size_t HPDF_UINT ;
typedef  TYPE_1__* HPDF_String ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_ParseText_Rec ;
typedef  scalar_t__ HPDF_INT32 ;
typedef  scalar_t__ HPDF_Encrypt ;
typedef  scalar_t__ HPDF_ByteType ;
typedef  scalar_t__ HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_BYTE_TYPE_LEAD ; 
 scalar_t__ HPDF_BYTE_TYPE_TRIAL ; 
 scalar_t__ HPDF_Encoder_ByteType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_Encoder_SetParseText (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Encoder_ToUnicode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Encrypt_Reset (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_MemCpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 size_t HPDF_StrLen (char*,int) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteBinary (int /*<<< orphan*/ ,scalar_t__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  HPDF_Stream_WriteEscapeText (int /*<<< orphan*/ ,char*) ; 
 int HPDF_TEXT_DEFAULT_LEN ; 
 int /*<<< orphan*/  HPDF_UInt16Swap (int /*<<< orphan*/ *) ; 
 scalar_t__* UNICODE_HEADER ; 

HPDF_STATUS
HPDF_String_Write  (HPDF_String   obj,
                    HPDF_Stream   stream,
                    HPDF_Encrypt  e)
{
    HPDF_STATUS ret;

    /*
     *  When encoder is not NULL, text is changed to unicode using encoder,
     *  and it outputs by HPDF_write_binary method.
     */

    HPDF_PTRACE((" HPDF_String_Write\n"));

    if (e)
        HPDF_Encrypt_Reset (e);

    if (obj->encoder == NULL) {
        if (e) {
            if ((ret = HPDF_Stream_WriteChar (stream, '<')) != HPDF_OK)
                return ret;

            if ((ret = HPDF_Stream_WriteBinary (stream, obj->value,
                    HPDF_StrLen ((char *)obj->value, -1), e)) != HPDF_OK)
                return ret;

            return HPDF_Stream_WriteChar (stream, '>');
        } else {
            return HPDF_Stream_WriteEscapeText (stream, (char *)obj->value);
        }
    } else {
        HPDF_BYTE* src = obj->value;
        HPDF_BYTE buf[HPDF_TEXT_DEFAULT_LEN * 2];
        HPDF_UINT tmp_len = 0;
        HPDF_BYTE* pbuf = buf;
        HPDF_INT32 len = obj->len;
        HPDF_ParseText_Rec  parse_state;
        HPDF_UINT i;

        if ((ret = HPDF_Stream_WriteChar (stream, '<')) != HPDF_OK)
           return ret;

        if ((ret = HPDF_Stream_WriteBinary (stream, UNICODE_HEADER, 2, e))
                        != HPDF_OK)
            return ret;

        HPDF_Encoder_SetParseText (obj->encoder, &parse_state, src, len);

        for (i = 0; (HPDF_INT32)i < len; i++) {
            HPDF_BYTE b = src[i];
            HPDF_UNICODE tmp_unicode;
            HPDF_ByteType btype = HPDF_Encoder_ByteType (obj->encoder,
                    &parse_state);

            if (tmp_len >= HPDF_TEXT_DEFAULT_LEN - 1) {
                if ((ret = HPDF_Stream_WriteBinary (stream, buf,
                            tmp_len * 2, e)) != HPDF_OK)
                    return ret;

                tmp_len = 0;
                pbuf = buf;
            }

            if (btype != HPDF_BYTE_TYPE_TRIAL) {
                if (btype == HPDF_BYTE_TYPE_LEAD) {
                    HPDF_BYTE b2 = src[i + 1];
                    HPDF_UINT16 char_code = (HPDF_UINT16)((HPDF_UINT) b * 256 + b2);

                    tmp_unicode = HPDF_Encoder_ToUnicode (obj->encoder,
                                char_code);
                } else {
                    tmp_unicode = HPDF_Encoder_ToUnicode (obj->encoder, b);
                }

                HPDF_UInt16Swap (&tmp_unicode);
                HPDF_MemCpy (pbuf, (HPDF_BYTE*)&tmp_unicode, 2);
                pbuf += 2;
                tmp_len++;
            }
        }

        if (tmp_len > 0) {
            if ((ret = HPDF_Stream_WriteBinary (stream, buf, tmp_len * 2, e))
                            != HPDF_OK)
                return ret;
        }

        if ((ret = HPDF_Stream_WriteChar (stream, '>')) != HPDF_OK)
            return ret;
    }

    return HPDF_OK;
}