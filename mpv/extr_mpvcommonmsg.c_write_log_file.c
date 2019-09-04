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
struct mp_log_root {int /*<<< orphan*/  log_file; } ;
struct mp_log {char* verbose_prefix; int /*<<< orphan*/  terminal_level; struct mp_log_root* root; } ;

/* Variables and functions */
 int MPMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MP_START_TIME ; 
 int /*<<< orphan*/  MSGL_DEBUG ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char*,char*) ; 
 int** mp_log_levels ; 
 int mp_time_us () ; 

__attribute__((used)) static void write_log_file(struct mp_log *log, int lev, char *text)
{
    struct mp_log_root *root = log->root;

    if (!root->log_file || lev > MPMAX(MSGL_DEBUG, log->terminal_level))
        return;

    fprintf(root->log_file, "[%8.3f][%c][%s] %s",
            (mp_time_us() - MP_START_TIME) / 1e6,
            mp_log_levels[lev][0],
            log->verbose_prefix, text);
    fflush(root->log_file);
}