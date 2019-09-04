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
typedef  int /*<<< orphan*/  uint32_t ;
struct vo {struct priv* priv; } ;
struct priv {int reload_display; int /*<<< orphan*/  display_mutex; int /*<<< orphan*/  display_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vo_wakeup (struct vo*) ; 

__attribute__((used)) static void tv_callback(void *callback_data, uint32_t reason, uint32_t param1,
                        uint32_t param2)
{
    struct vo *vo = callback_data;
    struct priv *p = vo->priv;
    pthread_mutex_lock(&p->display_mutex);
    p->reload_display = true;
    pthread_cond_signal(&p->display_cond);
    pthread_mutex_unlock(&p->display_mutex);
    vo_wakeup(vo);
}