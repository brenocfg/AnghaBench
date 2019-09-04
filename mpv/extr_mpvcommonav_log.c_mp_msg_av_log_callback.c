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
typedef  int /*<<< orphan*/  va_list ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {char* (* item_name ) (void*) ;} ;
typedef  TYPE_1__ AVClass ;

/* Variables and functions */
 int /*<<< orphan*/  MPMAX (int,int /*<<< orphan*/ ) ; 
 int MPMIN (int /*<<< orphan*/ ,int) ; 
 int av_log_level_to_mp_level (int) ; 
 struct mp_log* get_av_log (void*) ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  log_mpv_instance ; 
 int log_print_prefix ; 
 int /*<<< orphan*/  mp_msg (struct mp_log*,int,char*,char*) ; 
 scalar_t__ mp_msg_test (struct mp_log*,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 
 char* stub1 (void*) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mp_msg_av_log_callback(void *ptr, int level, const char *fmt,
                                   va_list vl)
{
    AVClass *avc = ptr ? *(AVClass **)ptr : NULL;
    int mp_level = av_log_level_to_mp_level(level);

    // Note: mp_log is thread-safe, but destruction of the log instances is not.
    pthread_mutex_lock(&log_lock);

    if (!log_mpv_instance) {
        pthread_mutex_unlock(&log_lock);
        // Fallback to stderr
        vfprintf(stderr, fmt, vl);
        return;
    }

    struct mp_log *log = get_av_log(ptr);

    if (mp_msg_test(log, mp_level)) {
        char buffer[4096] = "";
        int pos = 0;
        const char *prefix = avc ? avc->item_name(ptr) : NULL;
        if (log_print_prefix && prefix)
            pos = snprintf(buffer, sizeof(buffer), "%s: ", prefix);
        log_print_prefix = fmt[strlen(fmt) - 1] == '\n';

        pos = MPMIN(MPMAX(pos, 0), sizeof(buffer));
        vsnprintf(buffer + pos, sizeof(buffer) - pos, fmt, vl);

        mp_msg(log, mp_level, "%s", buffer);
    }

    pthread_mutex_unlock(&log_lock);
}