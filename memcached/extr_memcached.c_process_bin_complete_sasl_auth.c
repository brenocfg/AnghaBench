#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int nkey; int nbytes; } ;
typedef  TYPE_5__ item ;
struct TYPE_17__ {int keylen; int bodylen; } ;
struct TYPE_18__ {TYPE_1__ request; } ;
struct TYPE_22__ {int item; int cmd; int sasl_started; int sfd; int authenticated; TYPE_4__* thread; void* write_and_go; int /*<<< orphan*/  sasl_conn; TYPE_2__ binary_header; } ;
typedef  TYPE_6__ conn ;
struct TYPE_23__ {int sasl; scalar_t__ verbose; } ;
struct TYPE_19__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  auth_errors; int /*<<< orphan*/  auth_cmds; } ;
struct TYPE_20__ {TYPE_3__ stats; } ;

/* Variables and functions */
 char* ITEM_data (TYPE_5__*) ; 
 int /*<<< orphan*/  ITEM_key (TYPE_5__*) ; 
#define  PROTOCOL_BINARY_CMD_SASL_AUTH 131 
#define  PROTOCOL_BINARY_CMD_SASL_STEP 130 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_AUTH_CONTINUE ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_AUTH_ERROR ; 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_EINVAL ; 
#define  SASL_CONTINUE 129 
#define  SASL_OK 128 
 int /*<<< orphan*/  add_bin_header (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  add_iov (TYPE_6__*,char const*,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  conn_mwrite ; 
 void* conn_new_cmd ; 
 int /*<<< orphan*/  conn_set_state (TYPE_6__*,int /*<<< orphan*/ ) ; 
 void* conn_swallow ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_sasl_conn (TYPE_6__*) ; 
 int /*<<< orphan*/  item_unlink (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int sasl_server_start (int /*<<< orphan*/ ,char*,char const*,int,char const**,unsigned int*) ; 
 int sasl_server_step (int /*<<< orphan*/ ,char const*,int,char const**,unsigned int*) ; 
 TYPE_9__ settings ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  write_bin_error (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_bin_response (TYPE_6__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_bin_complete_sasl_auth(conn *c) {
    assert(settings.sasl);
    const char *out = NULL;
    unsigned int outlen = 0;

    assert(c->item);
    init_sasl_conn(c);

    int nkey = c->binary_header.request.keylen;
    int vlen = c->binary_header.request.bodylen - nkey;

    if (nkey > ((item*) c->item)->nkey) {
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_EINVAL, NULL, vlen);
        c->write_and_go = conn_swallow;
        item_unlink(c->item);
        return;
    }

    char mech[nkey+1];
    memcpy(mech, ITEM_key((item*)c->item), nkey);
    mech[nkey] = 0x00;

    if (settings.verbose)
        fprintf(stderr, "mech:  ``%s'' with %d bytes of data\n", mech, vlen);

    const char *challenge = vlen == 0 ? NULL : ITEM_data((item*) c->item);

    if (vlen > ((item*) c->item)->nbytes) {
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_EINVAL, NULL, vlen);
        c->write_and_go = conn_swallow;
        item_unlink(c->item);
        return;
    }

    int result=-1;

    switch (c->cmd) {
    case PROTOCOL_BINARY_CMD_SASL_AUTH:
        result = sasl_server_start(c->sasl_conn, mech,
                                   challenge, vlen,
                                   &out, &outlen);
        c->sasl_started = (result == SASL_OK || result == SASL_CONTINUE);
        break;
    case PROTOCOL_BINARY_CMD_SASL_STEP:
        if (!c->sasl_started) {
            if (settings.verbose) {
                fprintf(stderr, "%d: SASL_STEP called but sasl_server_start "
                        "not called for this connection!\n", c->sfd);
            }
            break;
        }
        result = sasl_server_step(c->sasl_conn,
                                  challenge, vlen,
                                  &out, &outlen);
        break;
    default:
        assert(false); /* CMD should be one of the above */
        /* This code is pretty much impossible, but makes the compiler
           happier */
        if (settings.verbose) {
            fprintf(stderr, "Unhandled command %d with challenge %s\n",
                    c->cmd, challenge);
        }
        break;
    }

    item_unlink(c->item);

    if (settings.verbose) {
        fprintf(stderr, "sasl result code:  %d\n", result);
    }

    switch(result) {
    case SASL_OK:
        c->authenticated = true;
        write_bin_response(c, "Authenticated", 0, 0, strlen("Authenticated"));
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.auth_cmds++;
        pthread_mutex_unlock(&c->thread->stats.mutex);
        break;
    case SASL_CONTINUE:
        add_bin_header(c, PROTOCOL_BINARY_RESPONSE_AUTH_CONTINUE, 0, 0, outlen);
        if(outlen > 0) {
            add_iov(c, out, outlen);
        }
        conn_set_state(c, conn_mwrite);
        c->write_and_go = conn_new_cmd;
        break;
    default:
        if (settings.verbose)
            fprintf(stderr, "Unknown sasl response:  %d\n", result);
        write_bin_error(c, PROTOCOL_BINARY_RESPONSE_AUTH_ERROR, NULL, 0);
        pthread_mutex_lock(&c->thread->stats.mutex);
        c->thread->stats.auth_cmds++;
        c->thread->stats.auth_errors++;
        pthread_mutex_unlock(&c->thread->stats.mutex);
    }
}