#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct Output* directory; scalar_t__ filesize; scalar_t__ period; } ;
struct TYPE_3__ {struct Output* stylesheet; } ;
struct Output {struct Output* filename; TYPE_2__ rotate; TYPE_1__ xml; scalar_t__ fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*) ; 
 int /*<<< orphan*/  close_rotate (struct Output*,scalar_t__) ; 
 int /*<<< orphan*/  free (struct Output*) ; 
 int /*<<< orphan*/  output_do_rotate (struct Output*,int) ; 

void
output_destroy(struct Output *out)
{
    if (out == NULL)
        return;

    /* If rotating files, then do one last rotate of this file to the
     * destination directory */
    if (out->rotate.period || out->rotate.filesize) {
        LOG(1, "doing finale rotate\n");
        output_do_rotate(out, 1);
    }

    /* If not rotating files, then simply close this file. Remember
     * that some files will write closing information before closing
     * the file */
    if (out->fp)
        close_rotate(out, out->fp);



    free(out->xml.stylesheet);
    free(out->rotate.directory);
    free(out->filename);

    free(out);
}