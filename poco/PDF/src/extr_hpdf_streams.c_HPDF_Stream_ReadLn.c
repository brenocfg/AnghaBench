#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  error; int /*<<< orphan*/  read_fn; int /*<<< orphan*/  seek_fn; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_INVALID_OPERATION ; 
 scalar_t__ HPDF_INVALID_PARAMETER ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_CUR ; 
 int HPDF_STREAM_BUF_SIZ ; 
 scalar_t__ HPDF_STREAM_EOF ; 
 scalar_t__ HPDF_STREAM_READLN_CONTINUE ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_Stream_Read (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ HPDF_Stream_Seek (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Stream_ReadLn  (HPDF_Stream  stream,
                     char    *s,
                     HPDF_UINT    *size)
{
    char buf[HPDF_STREAM_BUF_SIZ];
    HPDF_UINT r_size = *size;
    HPDF_UINT read_size = HPDF_STREAM_BUF_SIZ;

    HPDF_PTRACE((" HPDF_Stream_ReadLn\n"));

    if (!stream)
        return HPDF_INVALID_PARAMETER;

    if (!s || *size == 0)
        return HPDF_SetError (stream->error, HPDF_INVALID_PARAMETER, 0);

    if (!(stream->seek_fn) || !(stream->read_fn))
        return HPDF_SetError (stream->error, HPDF_INVALID_OPERATION, 0);

    if (r_size < HPDF_STREAM_BUF_SIZ)
        read_size = r_size;

    *size = 0;

    while (r_size > 1) {
        char *pbuf = buf;
        HPDF_STATUS ret = HPDF_Stream_Read (stream, (HPDF_BYTE *)buf, &read_size);

        if (ret != HPDF_OK && read_size == 0)
            return ret;

        r_size -= read_size;

        while (read_size > 0) {
            if (*pbuf == 0x0A || *pbuf == 0x0D) {
                *s = 0;
                read_size--;

                /* handling CR-LF marker */
                if (*pbuf == 0x0D || read_size > 1) {
                    pbuf++;

                    if (*pbuf == 0x0A)
                        read_size--;
                }

                if (read_size > 0)
                    return HPDF_Stream_Seek (stream, 0 - read_size,
                                HPDF_SEEK_CUR);
                else
                    return HPDF_OK;
            }

            *s++ = *pbuf++;
            read_size--;
            (*size)++;
        }

        if (r_size < HPDF_STREAM_BUF_SIZ)
            read_size = r_size;
        else
            read_size = HPDF_STREAM_BUF_SIZ;

        if (ret == HPDF_STREAM_EOF)
            return HPDF_STREAM_EOF;
    }

    *s = 0;

    return HPDF_STREAM_READLN_CONTINUE;
}