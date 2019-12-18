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
typedef  int HPDF_WhenceMode ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_INT ;
typedef  int /*<<< orphan*/  HPDF_FILEP ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FILE_IO_ERROR ; 
 scalar_t__ HPDF_FSEEK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
#define  HPDF_SEEK_CUR 129 
#define  HPDF_SEEK_END 128 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 

HPDF_STATUS
HPDF_FileReader_SeekFunc  (HPDF_Stream     stream,
                           HPDF_INT         pos,
                           HPDF_WhenceMode  mode)
{
    HPDF_FILEP fp = (HPDF_FILEP)stream->attr;
    HPDF_INT whence;

    HPDF_PTRACE((" HPDF_FileReader_SeekFunc\n"));

    switch (mode) {
        case HPDF_SEEK_CUR:
            whence = SEEK_CUR;
            break;
        case HPDF_SEEK_END:
            whence = SEEK_END;
            break;
        default:
            whence = SEEK_SET;
    }

    if (HPDF_FSEEK (fp, pos, whence) != 0) {
        return HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR, HPDF_FERROR(fp));
    }

    return HPDF_OK;
}