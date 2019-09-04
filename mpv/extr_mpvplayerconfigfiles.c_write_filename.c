#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  write_name ;
struct MPContext {TYPE_1__* opts; } ;
struct TYPE_2__ {scalar_t__ write_filename_in_watch_later_config; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static void write_filename(struct MPContext *mpctx, FILE *file, char *filename)
{
    if (mpctx->opts->write_filename_in_watch_later_config) {
        char write_name[1024] = {0};
        for (int n = 0; filename[n] && n < sizeof(write_name) - 1; n++)
            write_name[n] = (unsigned char)filename[n] < 32 ? '_' : filename[n];
        fprintf(file, "# %s\n", write_name);
    }
}