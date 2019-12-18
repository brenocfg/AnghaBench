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
struct subprocess_args {int /*<<< orphan*/  log; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mp_msg_flush_status_line (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_subprocess (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  talloc_free (struct subprocess_args*) ; 

__attribute__((used)) static void *run_subprocess(void *ptr)
{
    struct subprocess_args *p = ptr;
    pthread_detach(pthread_self());

    mp_msg_flush_status_line(p->log);

    char *err = NULL;
    if (mp_subprocess(p->args, NULL, NULL, NULL, NULL, &err) < 0)
        mp_err(p->log, "Running subprocess failed: %s\n", err);

    talloc_free(p);
    return NULL;
}