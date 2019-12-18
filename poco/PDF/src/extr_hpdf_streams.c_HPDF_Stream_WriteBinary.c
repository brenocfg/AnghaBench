#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mmgr; } ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  scalar_t__ HPDF_Encrypt ;
typedef  int HPDF_BYTE ;
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Encrypt_CryptBuf (scalar_t__,int const*,int*,int) ; 
 scalar_t__ HPDF_FALSE ; 
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Stream_Write (TYPE_1__*,int*,int) ; 
 int HPDF_TEXT_DEFAULT_LEN ; 
 scalar_t__ HPDF_TRUE ; 

HPDF_STATUS
HPDF_Stream_WriteBinary  (HPDF_Stream      stream,
                          const HPDF_BYTE  *data,
                          HPDF_UINT        len,
                          HPDF_Encrypt     e)
{
    char buf[HPDF_TEXT_DEFAULT_LEN];
    HPDF_BYTE ebuf[HPDF_TEXT_DEFAULT_LEN];
    HPDF_BYTE *pbuf = NULL;
    HPDF_BOOL flg = HPDF_FALSE;
    HPDF_UINT idx = 0;
    HPDF_UINT i;
    const HPDF_BYTE* p;
    HPDF_STATUS ret = HPDF_OK;

    HPDF_PTRACE((" HPDF_Stream_WriteBinary\n"));

    if (e) {
        if (len <= HPDF_TEXT_DEFAULT_LEN)
            pbuf = ebuf;
        else {
            pbuf = (HPDF_BYTE *)HPDF_GetMem (stream->mmgr, len);
            flg = HPDF_TRUE;
        }

        HPDF_Encrypt_CryptBuf (e, data, pbuf, len);
        p = pbuf;
    } else {
        p = data;
    }

    for (i = 0; i < len; i++, p++) {
        char c = (char)(*p >> 4);

        if (c <= 9)
            c += 0x30;
        else
            c += 0x41 - 10;
        buf[idx++] = c;

        c = (char)(*p & 0x0f);
        if (c <= 9)
            c += 0x30;
        else
            c += 0x41 - 10;
        buf[idx++] = c;

        if (idx > HPDF_TEXT_DEFAULT_LEN - 2) {
            ret = HPDF_Stream_Write (stream, (HPDF_BYTE *)buf, idx);
            if (ret != HPDF_OK) {
                if (flg)
                    HPDF_FreeMem (stream->mmgr, pbuf);
                return ret;
            }
            idx = 0;
        }
    }

    if (idx > 0) {
        ret = HPDF_Stream_Write (stream, (HPDF_BYTE *)buf, idx);
    }

    if (flg)
        HPDF_FreeMem (stream->mmgr, pbuf);

    return ret;
}