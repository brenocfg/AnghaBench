#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  void* rel_time_t ;
struct TYPE_18__ {int /*<<< orphan*/  expiration; } ;
struct TYPE_19__ {TYPE_3__ body; } ;
struct TYPE_22__ {TYPE_4__ message; } ;
typedef  TYPE_7__ protocol_binary_request_flush ;
struct TYPE_16__ {int extlen; } ;
struct TYPE_17__ {TYPE_1__ request; } ;
struct TYPE_23__ {TYPE_6__* thread; TYPE_2__ binary_header; } ;
typedef  TYPE_8__ conn ;
struct TYPE_20__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  flush_cmds; } ;
struct TYPE_21__ {TYPE_5__ stats; } ;
struct TYPE_15__ {scalar_t__ oldest_live; int /*<<< orphan*/  oldest_cas; scalar_t__ use_cas; int /*<<< orphan*/  flush_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_AUTH_ERROR ; 
 TYPE_7__* binary_get_request (TYPE_8__*) ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  get_cas_id () ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* realtime (scalar_t__) ; 
 TYPE_11__ settings ; 
 int /*<<< orphan*/  write_bin_error (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bin_response (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_bin_flush(conn *c) {
    time_t exptime = 0;
    protocol_binary_request_flush* req = binary_get_request(c);
    rel_time_t new_oldest = 0;

    if (!settings.flush_enabled) {
      // flush_all is not allowed but we log it on stats
      write_bin_error(c, PROTOCOL_BINARY_RESPONSE_AUTH_ERROR, NULL, 0);
      return;
    }

    if (c->binary_header.request.extlen == sizeof(req->message.body)) {
        exptime = ntohl(req->message.body.expiration);
    }

    if (exptime > 0) {
        new_oldest = realtime(exptime);
    } else {
        new_oldest = current_time;
    }
    if (settings.use_cas) {
        settings.oldest_live = new_oldest - 1;
        if (settings.oldest_live <= current_time)
            settings.oldest_cas = get_cas_id();
    } else {
        settings.oldest_live = new_oldest;
    }

    pthread_mutex_lock(&c->thread->stats.mutex);
    c->thread->stats.flush_cmds++;
    pthread_mutex_unlock(&c->thread->stats.mutex);

    write_bin_response(c, NULL, 0, 0, 0);
}