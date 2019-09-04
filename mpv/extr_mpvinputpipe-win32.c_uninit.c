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
struct priv {int /*<<< orphan*/  fd; scalar_t__ close_fd; int /*<<< orphan*/  thread; } ;
struct mp_input_src {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_input_src*,char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uninit(struct mp_input_src *src)
{
    struct priv *p = src->priv;

    CloseHandle(p->thread);
    if (p->close_fd)
        close(p->fd);

    MP_VERBOSE(src, "Exited.\n");
}