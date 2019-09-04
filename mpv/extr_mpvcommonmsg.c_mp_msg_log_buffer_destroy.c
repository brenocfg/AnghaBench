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
struct mp_log_root {int num_buffers; int /*<<< orphan*/  reload_counter; struct mp_log_buffer_entry** buffers; } ;
struct mp_log_buffer_entry {struct mp_log_root* root; } ;
struct mp_log_buffer {struct mp_log_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct mp_log_buffer_entry**,int,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_msg_lock ; 
 struct mp_log_buffer_entry* mp_msg_log_buffer_read (struct mp_log_buffer_entry*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (struct mp_log_buffer_entry*) ; 

void mp_msg_log_buffer_destroy(struct mp_log_buffer *buffer)
{
    if (!buffer)
        return;

    pthread_mutex_lock(&mp_msg_lock);

    struct mp_log_root *root = buffer->root;
    for (int n = 0; n < root->num_buffers; n++) {
        if (root->buffers[n] == buffer) {
            MP_TARRAY_REMOVE_AT(root->buffers, root->num_buffers, n);
            goto found;
        }
    }

    abort();

found:

    while (1) {
        struct mp_log_buffer_entry *e = mp_msg_log_buffer_read(buffer);
        if (!e)
            break;
        talloc_free(e);
    }
    talloc_free(buffer);

    atomic_fetch_add(&root->reload_counter, 1);
    pthread_mutex_unlock(&mp_msg_lock);
}