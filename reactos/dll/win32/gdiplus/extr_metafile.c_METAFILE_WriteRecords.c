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
struct TYPE_3__ {int comment_data_length; int /*<<< orphan*/  comment_data; int /*<<< orphan*/  record_dc; } ;
typedef  TYPE_1__ GpMetafile ;

/* Variables and functions */
 int /*<<< orphan*/  GdiComment (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void METAFILE_WriteRecords(GpMetafile *metafile)
{
    if (metafile->comment_data_length > 4)
    {
        GdiComment(metafile->record_dc, metafile->comment_data_length, metafile->comment_data);
        metafile->comment_data_length = 4;
    }
}