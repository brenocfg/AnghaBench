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
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_INT32 ;
typedef  int /*<<< orphan*/  HPDF_FILEP ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_FILE_IO_ERROR ; 
 int /*<<< orphan*/  HPDF_FTELL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_INT32
HPDF_FileStream_TellFunc  (HPDF_Stream   stream)
{
    HPDF_INT32 ret;
    HPDF_FILEP fp = (HPDF_FILEP)stream->attr;

    HPDF_PTRACE((" HPDF_FileReader_TellFunc\n"));

    if ((ret = HPDF_FTELL (fp)) < 0) {
        return HPDF_SetError (stream->error, HPDF_FILE_IO_ERROR,
                HPDF_FERROR(fp));
    }

    return ret;
}