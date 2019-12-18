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
struct vo_x11_state {int ShmCompletionWaitCount; } ;
struct vo {struct vo_x11_state* x11; struct priv* priv; } ;
struct priv {int Shm_Warned_Slow; scalar_t__ Shmem_Flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct vo*,char*) ; 
 int /*<<< orphan*/  mp_sleep_us (int) ; 
 int /*<<< orphan*/  vo_x11_check_events (struct vo*) ; 

__attribute__((used)) static void wait_for_completion(struct vo *vo, int max_outstanding)
{
    struct priv *ctx = vo->priv;
    struct vo_x11_state *x11 = vo->x11;
    if (ctx->Shmem_Flag) {
        while (x11->ShmCompletionWaitCount > max_outstanding) {
            if (!ctx->Shm_Warned_Slow) {
                MP_WARN(vo, "can't keep up! Waiting"
                            " for XShm completion events...\n");
                ctx->Shm_Warned_Slow = 1;
            }
            mp_sleep_us(1000);
            vo_x11_check_events(vo);
        }
    }
}