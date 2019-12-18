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
struct mp_ipc_ctx {int /*<<< orphan*/  client_api; } ;
struct client_arg {int /*<<< orphan*/  client_h; int /*<<< orphan*/  client; int /*<<< orphan*/  log; int /*<<< orphan*/  client_name; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_thread ; 
 int /*<<< orphan*/  mp_client_get_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_new_client (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpv_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct client_arg*) ; 
 int /*<<< orphan*/  talloc_free (struct client_arg*) ; 

__attribute__((used)) static void ipc_start_client(struct mp_ipc_ctx *ctx, struct client_arg *client)
{
    client->client = mp_new_client(ctx->client_api, client->client_name),
    client->log    = mp_client_get_log(client->client);

    pthread_t client_thr;
    if (pthread_create(&client_thr, NULL, client_thread, client)) {
        mpv_destroy(client->client);
        CloseHandle(client->client_h);
        talloc_free(client);
    }
}