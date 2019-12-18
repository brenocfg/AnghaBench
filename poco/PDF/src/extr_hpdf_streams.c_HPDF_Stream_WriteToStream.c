#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  error; int /*<<< orphan*/  write_fn; } ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  scalar_t__ HPDF_Encrypt ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;
typedef  scalar_t__ HPDF_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Encrypt_CryptBuf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_FALSE ; 
 scalar_t__ HPDF_INVALID_OBJECT ; 
 scalar_t__ HPDF_NOERROR ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 int HPDF_STREAM_BUF_SIZ ; 
 scalar_t__ HPDF_STREAM_EOF ; 
 int HPDF_STREAM_FILTER_FLATE_DECODE ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Read (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ HPDF_Stream_Seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Size (TYPE_1__*) ; 
 scalar_t__ HPDF_Stream_Write (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_Stream_WriteToStreamWithDeflate (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 scalar_t__ HPDF_THIS_FUNC_WAS_SKIPPED ; 
 scalar_t__ HPDF_TRUE ; 
 int /*<<< orphan*/  HPDF_UNUSED (int) ; 

HPDF_STATUS
HPDF_Stream_WriteToStream  (HPDF_Stream  src,
                            HPDF_Stream  dst,
                            HPDF_UINT    filter,
                            HPDF_Encrypt  e)
{
    HPDF_STATUS ret;
    HPDF_BYTE buf[HPDF_STREAM_BUF_SIZ];
    HPDF_BYTE ebuf[HPDF_STREAM_BUF_SIZ];
    HPDF_BOOL flg;

    HPDF_PTRACE((" HPDF_Stream_WriteToStream\n"));
    HPDF_UNUSED (filter);

    if (!dst || !(dst->write_fn)) {
        HPDF_SetError (src->error, HPDF_INVALID_OBJECT, 0);
        return HPDF_INVALID_OBJECT;
    }

    if (HPDF_Error_GetCode (src->error) != HPDF_NOERROR ||
            HPDF_Error_GetCode (dst->error) != HPDF_NOERROR)
        return HPDF_THIS_FUNC_WAS_SKIPPED;

    /* initialize input stream */
    if (HPDF_Stream_Size (src) == 0)
        return HPDF_OK;

#ifndef LIBHPDF_HAVE_NOZLIB
    if (filter & HPDF_STREAM_FILTER_FLATE_DECODE)
        return HPDF_Stream_WriteToStreamWithDeflate (src, dst, e);
#endif /* LIBHPDF_HAVE_NOZLIB */

    ret = HPDF_Stream_Seek (src, 0, HPDF_SEEK_SET);
    if (ret != HPDF_OK)
        return ret;

    flg = HPDF_FALSE;
    for (;;) {
        HPDF_UINT size = HPDF_STREAM_BUF_SIZ;

        ret = HPDF_Stream_Read (src, buf, &size);

        if (ret != HPDF_OK) {
            if (ret == HPDF_STREAM_EOF) {
                flg = HPDF_TRUE;
                if (size == 0)
                    break;
            } else {
                return ret;
            }
        }

        if (e) {
            HPDF_Encrypt_CryptBuf (e, buf, ebuf, size);
            ret = HPDF_Stream_Write(dst, ebuf, size);
        } else {
            ret = HPDF_Stream_Write(dst, buf, size);
        }

        if (ret != HPDF_OK)
            return ret;

        if (flg)
            break;
    }

    return HPDF_OK;
}