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
struct MPContext {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 char* mp_get_playback_resume_config_filename (struct MPContext*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  write_filename (struct MPContext*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void write_redirect(struct MPContext *mpctx, char *path)
{
    char *conffile = mp_get_playback_resume_config_filename(mpctx, path);
    if (conffile) {
        FILE *file = fopen(conffile, "wb");
        if (file) {
            fprintf(file, "# redirect entry\n");
            write_filename(mpctx, file, path);
            fclose(file);
        }
        talloc_free(conffile);
    }
}