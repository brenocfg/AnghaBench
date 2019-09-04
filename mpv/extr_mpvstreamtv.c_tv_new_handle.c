#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chanlist; int norm; int channel; int /*<<< orphan*/  const* functions; struct mp_log* log; void* priv; } ;
typedef  TYPE_1__ tvi_handle_t ;
typedef  int /*<<< orphan*/  tvi_functions_t ;
struct mp_log {int dummy; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

tvi_handle_t *tv_new_handle(int size, struct mp_log *log, const tvi_functions_t *functions)
{
    tvi_handle_t *h = calloc(1, sizeof(*h));

    if (!h)
        return NULL;

    h->priv = calloc(1, size);

    if (!h->priv) {
        free(h);
        return NULL;
    }

    h->log        = log;
    h->functions  = functions;
    h->chanlist   = -1;
    h->norm       = -1;
    h->channel    = -1;

    return h;
}