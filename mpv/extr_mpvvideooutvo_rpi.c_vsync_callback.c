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
struct vo {struct priv* priv; } ;
struct priv {int vsync_counter; int /*<<< orphan*/  display_mutex; int /*<<< orphan*/  display_cond; } ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vsync_callback(DISPMANX_UPDATE_HANDLE_T u, void *arg)
{
    struct vo *vo = arg;
    struct priv *p = vo->priv;
    pthread_mutex_lock(&p->display_mutex);
    p->vsync_counter += 1;
    pthread_cond_signal(&p->display_cond);
    pthread_mutex_unlock(&p->display_mutex);
}