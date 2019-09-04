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
struct mp_log {int dummy; } ;
struct TYPE_2__ {struct mp_log* log; } ;

/* Variables and functions */
 int MSGL_ERR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mp_msg (struct mp_log*,int,char*,char const*) ; 
 int num_va_mpv_clients ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  va_log_mutex ; 
 TYPE_1__** va_mpv_clients ; 

__attribute__((used)) static void va_message_callback(const char *msg, int mp_level)
{
    pthread_mutex_lock(&va_log_mutex);

    if (num_va_mpv_clients) {
        struct mp_log *dst = va_mpv_clients[num_va_mpv_clients - 1]->log;
        mp_msg(dst, mp_level, "libva: %s", msg);
    } else {
        // We can't get or call the original libva handler (vaSet... return
        // them, but it might be from some other lib etc.). So just do what
        // libva happened to do at the time of this writing.
        if (mp_level <= MSGL_ERR) {
            fprintf(stderr, "libva error: %s", msg);
        } else {
            fprintf(stderr, "libva info: %s", msg);
        }
    }

    pthread_mutex_unlock(&va_log_mutex);
}