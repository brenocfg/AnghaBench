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
struct priv {int /*<<< orphan*/  file; int /*<<< orphan*/  thread; int /*<<< orphan*/  cancel_requested; } ;
struct mp_input_src {struct priv* priv; } ;

/* Variables and functions */
 scalar_t__ CancelIoEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_input_src*,char*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void request_cancel(struct mp_input_src *src)
{
    struct priv *p = src->priv;

    MP_VERBOSE(src, "Exiting...\n");
    atomic_store(&p->cancel_requested, true);

    // The thread might not be peforming I/O at the exact moment when
    // CancelIoEx is called, so call it in a loop until it succeeds or the
    // thread exits
    do {
        if (CancelIoEx(p->file, NULL))
            break;
    } while (WaitForSingleObject(p->thread, 1) != WAIT_OBJECT_0);
}