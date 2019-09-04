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
struct mpv_handle {int num_properties; scalar_t__ lowest_changed; int /*<<< orphan*/  lock; TYPE_1__** properties; } ;
struct mp_client_api {int num_clients; int /*<<< orphan*/  lock; struct mpv_handle** clients; } ;
struct MPContext {struct mp_client_api* clients; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mark_property_changed (struct mpv_handle*,int) ; 
 int mp_get_property_id (struct MPContext*,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_client (struct mpv_handle*) ; 

void mp_client_property_change(struct MPContext *mpctx, const char *name)
{
    struct mp_client_api *clients = mpctx->clients;
    int id = mp_get_property_id(mpctx, name);

    pthread_mutex_lock(&clients->lock);

    for (int n = 0; n < clients->num_clients; n++) {
        struct mpv_handle *client = clients->clients[n];
        pthread_mutex_lock(&client->lock);
        for (int i = 0; i < client->num_properties; i++) {
            if (client->properties[i]->id == id)
                mark_property_changed(client, i);
        }
        if (client->lowest_changed < client->num_properties)
            wakeup_client(client);
        pthread_mutex_unlock(&client->lock);
    }

    pthread_mutex_unlock(&clients->lock);
}