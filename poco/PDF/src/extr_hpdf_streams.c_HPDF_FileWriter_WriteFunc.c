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
struct TYPE_3__ {int /*<<< orphan*/  error; scalar_t__ attr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  scalar_t__ HPDF_FILEP ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FERROR (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_FILE_IO_ERROR ; 
 scalar_t__ HPDF_FWRITE (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_FileWriter_WriteFunc  (HPDF_Stream      stream,
                            const HPDF_BYTE  *ptr,
                            HPDF_UINT        siz)
{
    HPDF_FILEP fp;
    HPDF_UINT ret;

    HPDF_PTRACE((" HPDF_FileWriter_WriteFunc\n"));

    fp = (HPDF_FILEP)stream->attr;
    ret = HPDF_FWRITE (ptr, 1, siz, fp);

    if (ret != siz) {
        return HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR, HPDF_FERROR(fp));
    }

    return HPDF_OK;
}