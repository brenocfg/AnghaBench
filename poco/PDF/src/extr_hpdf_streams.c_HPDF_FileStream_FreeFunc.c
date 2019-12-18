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
struct TYPE_3__ {int /*<<< orphan*/ * attr; } ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_FILEP ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FCLOSE (scalar_t__) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

void
HPDF_FileStream_FreeFunc  (HPDF_Stream  stream)
{
    HPDF_FILEP fp;

    HPDF_PTRACE((" HPDF_FileStream_FreeFunc\n"));

    fp = (HPDF_FILEP)stream->attr;

    if (fp)
        HPDF_FCLOSE(fp);

    stream->attr = NULL;
}