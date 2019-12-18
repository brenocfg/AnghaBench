#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct per_core_time_in_state_file {size_t filename; size_t last_ticks_len; int /*<<< orphan*/ * ff; TYPE_1__* last_ticks; } ;
struct per_core_single_number_file {int found; unsigned long long value; } ;
struct last_ticks {int dummy; } ;
struct cpu_chart {struct per_core_time_in_state_file time_in_state_files; struct per_core_single_number_file* files; } ;
struct TYPE_4__ {unsigned long long ticks; unsigned long long frequency; } ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  error (char*,size_t) ; 
 scalar_t__ keep_per_core_fds_open ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  procfile_close (int /*<<< orphan*/ *) ; 
 size_t procfile_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,size_t,int) ; 
 size_t procfile_linewords (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * procfile_open (size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 char* procfile_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* reallocz (TYPE_1__*,int) ; 
 unsigned long long str2ull (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int read_per_core_time_in_state_files(struct cpu_chart *all_cpu_charts, size_t len, size_t index) {
    size_t x, files_read = 0, files_nonzero = 0;

    for(x = 0; x < len ; x++) {
        struct per_core_single_number_file *f = &all_cpu_charts[x].files[index];
        struct per_core_time_in_state_file *tsf = &all_cpu_charts[x].time_in_state_files;

        f->found = 0;

        if(unlikely(!tsf->filename))
            continue;

        if(unlikely(!tsf->ff)) {
            tsf->ff = procfile_open(tsf->filename, " \t:", PROCFILE_FLAG_DEFAULT);
            if(unlikely(!tsf->ff))
            {
                error("Cannot open file '%s'", tsf->filename);
                continue;
            }
        }

        tsf->ff = procfile_readall(tsf->ff);
        if(unlikely(!tsf->ff)) {
            error("Cannot read file '%s'", tsf->filename);
            procfile_close(tsf->ff);
            tsf->ff = NULL;
            continue;
        }
        else {
            // successful read

            size_t lines = procfile_lines(tsf->ff), l;
            size_t words;
            unsigned long long total_ticks_since_last = 0, avg_freq = 0;

            // Check if there is at least one frequency in time_in_state
            if (procfile_word(tsf->ff, 0)[0] == '\0') {
                if(unlikely(keep_per_core_fds_open != CONFIG_BOOLEAN_YES)) {
                    procfile_close(tsf->ff);
                    tsf->ff = NULL;
                }
                // TODO: Is there a better way to avoid spikes than calculating the average over
                // the whole period under schedutil governor?
                // freez(tsf->last_ticks);
                // tsf->last_ticks = NULL;
                // tsf->last_ticks_len = 0;
                continue;
            }

            if (unlikely(tsf->last_ticks_len < lines || tsf->last_ticks == NULL)) {
                tsf->last_ticks = reallocz(tsf->last_ticks, sizeof(struct last_ticks) * lines);
                memset(tsf->last_ticks, 0, sizeof(struct last_ticks) * lines);
                tsf->last_ticks_len = lines;
            }

            f->value = 0;

            for(l = 0; l < lines - 1 ;l++) {
                unsigned long long frequency = 0, ticks = 0, ticks_since_last = 0;

                words = procfile_linewords(tsf->ff, l);
                if(unlikely(words < 2)) {
                    error("Cannot read time_in_state line. Expected 2 params, read %zu.", words);
                    continue;
                }
                frequency = str2ull(procfile_lineword(tsf->ff, l, 0));
                ticks     = str2ull(procfile_lineword(tsf->ff, l, 1));

                // It is assumed that frequencies are static and sorted
                ticks_since_last = ticks - tsf->last_ticks[l].ticks;
                tsf->last_ticks[l].frequency = frequency;
                tsf->last_ticks[l].ticks = ticks;

                total_ticks_since_last += ticks_since_last;
                avg_freq += frequency * ticks_since_last;

            }

            if (likely(total_ticks_since_last)) {
                avg_freq /= total_ticks_since_last;
                f->value = avg_freq;
            }

            if(unlikely(keep_per_core_fds_open != CONFIG_BOOLEAN_YES)) {
                procfile_close(tsf->ff);
                tsf->ff = NULL;
            }
        }

        files_read++;

        f->found = 1;

        if(likely(f->value != 0))
            files_nonzero++;
    }

    if(unlikely(files_read == 0))
        return -1;

    if(unlikely(files_nonzero == 0))
        return 0;

    return (int)files_nonzero;
}