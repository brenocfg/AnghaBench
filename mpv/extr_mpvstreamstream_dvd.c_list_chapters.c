#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tt_srpt_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  ifo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (int /*<<< orphan*/ *,char*,...) ; 
 int get_chapter_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,double*) ; 

__attribute__((used)) static void list_chapters(stream_t *stream, ifo_handle_t *vts_file, tt_srpt_t *tt_srpt, int title_no)
{
    MP_INFO(stream, "CHAPTERS: ");
    for (int n = 0; ; n++) {
        double p = n;
        int r;
        r = get_chapter_time(vts_file, tt_srpt, title_no, &p);
        if (!r)
            break;
        int t = p * 1000;
        MP_INFO(stream, "%02d:%02d:%02d.%03d,", t/3600000, (t/60000)%60, (t/1000)%60, t%1000);
    }
    MP_INFO(stream, "\n");
}