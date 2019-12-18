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
struct TYPE_3__ {int /*<<< orphan*/  error; int /*<<< orphan*/  attr; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_FILEP ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_FEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FILE_IO_ERROR ; 
 scalar_t__ HPDF_FREAD (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_STREAM_EOF ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_FileReader_ReadFunc  (HPDF_Stream  stream,
                          HPDF_BYTE    *ptr,
                          HPDF_UINT    *siz)
{
    HPDF_FILEP fp = (HPDF_FILEP)stream->attr;
    HPDF_UINT rsiz;

    HPDF_PTRACE((" HPDF_FileReader_ReadFunc\n"));

    HPDF_MemSet(ptr, 0, *siz);
    rsiz = HPDF_FREAD(ptr, 1, *siz, fp);

    if (rsiz != *siz) {
        if (HPDF_FEOF(fp)) {

            *siz = rsiz;

            return HPDF_STREAM_EOF;
        }

        return HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR, HPDF_FERROR(fp));
    }

    return HPDF_OK;
}