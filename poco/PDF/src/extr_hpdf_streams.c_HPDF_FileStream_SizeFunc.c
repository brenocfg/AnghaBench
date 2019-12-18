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
typedef  int /*<<< orphan*/  HPDF_UINT32 ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_INT ;
typedef  int /*<<< orphan*/  HPDF_FILEP ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FILE_IO_ERROR ; 
 scalar_t__ HPDF_FSEEK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FTELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 

HPDF_UINT32
HPDF_FileStream_SizeFunc  (HPDF_Stream   stream)
{
    HPDF_INT size;
    HPDF_INT ptr;
    HPDF_FILEP fp = (HPDF_FILEP)stream->attr;

    HPDF_PTRACE((" HPDF_FileReader_SizeFunc\n"));

    /* save current file-pointer */
    if ((ptr = HPDF_FTELL (fp)) < 0) {
        HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR,
                HPDF_FERROR(fp));
        return 0;
    }

    /* move file-pointer to the end of the file */
    if (HPDF_FSEEK (fp, 0, SEEK_END) < 0) {
        HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR,
                HPDF_FERROR(fp));
        return 0;
    }

    /* get the pointer of the end of the file */
    if ((size = HPDF_FTELL (fp)) < 0) {
        HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR,
                HPDF_FERROR(fp));
        return 0;
    }

    /* restore current file-pointer */
    if (HPDF_FSEEK (fp, ptr, SEEK_SET) < 0) {
        HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR,
                HPDF_FERROR(fp));
        return 0;
    }

    return (HPDF_UINT32)size;
}