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
struct thread_arg {int /*<<< orphan*/  client; int /*<<< orphan*/  fname; TYPE_1__* backend; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {char* name; scalar_t__ (* load ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct thread_arg*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 
 char* mpv_client_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpv_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct thread_arg*) ; 

__attribute__((used)) static void *script_thread(void *p)
{
    pthread_detach(pthread_self());

    struct thread_arg *arg = p;

    char name[90];
    snprintf(name, sizeof(name), "%s (%s)", arg->backend->name,
             mpv_client_name(arg->client));
    mpthread_set_name(name);

    if (arg->backend->load(arg->client, arg->fname) < 0)
        MP_ERR(arg, "Could not load %s %s\n", arg->backend->name, arg->fname);

    mpv_destroy(arg->client);
    talloc_free(arg);
    return NULL;
}