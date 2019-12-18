#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {void* expiration; void* flags; } ;
struct TYPE_30__ {TYPE_1__ body; } ;
struct TYPE_34__ {TYPE_2__ message; } ;
typedef  TYPE_6__ protocol_binary_request_set ;
struct TYPE_35__ {int it_flags; } ;
typedef  TYPE_7__ item ;
typedef  enum store_item_type { ____Placeholder_store_item_type } store_item_type ;
struct TYPE_32__ {int keylen; int bodylen; int extlen; int /*<<< orphan*/  cas; } ;
struct TYPE_33__ {TYPE_4__ request; } ;
struct TYPE_36__ {int cmd; int sfd; int sbytes; int rlbytes; int /*<<< orphan*/  substate; void* ritem; TYPE_7__* item; TYPE_5__ binary_header; int /*<<< orphan*/  write_and_go; TYPE_3__* thread; } ;
typedef  TYPE_8__ conn ;
struct TYPE_31__ {int /*<<< orphan*/  storage; int /*<<< orphan*/  l; } ;
struct TYPE_28__ {int verbose; scalar_t__ detail_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DONT_UPDATE ; 
 int ITEM_CHUNKED ; 
 int /*<<< orphan*/  ITEM_clsid (TYPE_7__*) ; 
 void* ITEM_data (TYPE_7__*) ; 
 scalar_t__ ITEM_get_cas (TYPE_7__*) ; 
 void* ITEM_schunk (TYPE_7__*) ; 
 int /*<<< orphan*/  ITEM_set_cas (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGGER_ITEM_STORE ; 
 int /*<<< orphan*/  LOGGER_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOG_MUTATIONS ; 
 int NO_MEMORY ; 
 int NREAD_ADD ; 
 int NREAD_CAS ; 
 int NREAD_REPLACE ; 
 int NREAD_SET ; 
#define  PROTOCOL_BINARY_CMD_ADD 130 
#define  PROTOCOL_BINARY_CMD_REPLACE 129 
#define  PROTOCOL_BINARY_CMD_SET 128 
 int /*<<< orphan*/  PROTOCOL_BINARY_RESPONSE_E2BIG ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int TOO_LARGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bin_read_set_value ; 
 char* binary_get_key (TYPE_8__*) ; 
 TYPE_6__* binary_get_request (TYPE_8__*) ; 
 int /*<<< orphan*/  conn_nread ; 
 int /*<<< orphan*/  conn_set_state (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_swallow ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_7__* item_alloc (char*,int,void*,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* item_get (char*,int,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_remove (TYPE_7__*) ; 
 int /*<<< orphan*/  item_size_ok (int,void*,int) ; 
 int /*<<< orphan*/  item_unlink (TYPE_7__*) ; 
 void* ntohl (void*) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  realtime (void*) ; 
 TYPE_10__ settings ; 
 int /*<<< orphan*/  stats_prefix_record_set (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_bin_error (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void process_bin_update(conn *c) {
    char *key;
    int nkey;
    int vlen;
    item *it;
    protocol_binary_request_set* req = binary_get_request(c);

    assert(c != NULL);

    key = binary_get_key(c);
    nkey = c->binary_header.request.keylen;

    /* fix byteorder in the request */
    req->message.body.flags = ntohl(req->message.body.flags);
    req->message.body.expiration = ntohl(req->message.body.expiration);

    vlen = c->binary_header.request.bodylen - (nkey + c->binary_header.request.extlen);

    if (settings.verbose > 1) {
        int ii;
        if (c->cmd == PROTOCOL_BINARY_CMD_ADD) {
            fprintf(stderr, "<%d ADD ", c->sfd);
        } else if (c->cmd == PROTOCOL_BINARY_CMD_SET) {
            fprintf(stderr, "<%d SET ", c->sfd);
        } else {
            fprintf(stderr, "<%d REPLACE ", c->sfd);
        }
        for (ii = 0; ii < nkey; ++ii) {
            fprintf(stderr, "%c", key[ii]);
        }

        fprintf(stderr, " Value len is %d", vlen);
        fprintf(stderr, "\n");
    }

    if (settings.detail_enabled) {
        stats_prefix_record_set(key, nkey);
    }

    it = item_alloc(key, nkey, req->message.body.flags,
            realtime(req->message.body.expiration), vlen+2);

    if (it == 0) {
        enum store_item_type status;
        if (! item_size_ok(nkey, req->message.body.flags, vlen + 2)) {
            write_bin_error(c, PROTOCOL_BINARY_RESPONSE_E2BIG, NULL, vlen);
            status = TOO_LARGE;
        } else {
            out_of_memory(c, "SERVER_ERROR Out of memory allocating item");
            /* This error generating method eats the swallow value. Add here. */
            c->sbytes = vlen;
            status = NO_MEMORY;
        }
        /* FIXME: losing c->cmd since it's translated below. refactor? */
        LOGGER_LOG(c->thread->l, LOG_MUTATIONS, LOGGER_ITEM_STORE,
                NULL, status, 0, key, nkey, req->message.body.expiration,
                ITEM_clsid(it), c->sfd);

        /* Avoid stale data persisting in cache because we failed alloc.
         * Unacceptable for SET. Anywhere else too? */
        if (c->cmd == PROTOCOL_BINARY_CMD_SET) {
            it = item_get(key, nkey, c, DONT_UPDATE);
            if (it) {
                item_unlink(it);
                STORAGE_delete(c->thread->storage, it);
                item_remove(it);
            }
        }

        /* swallow the data line */
        c->write_and_go = conn_swallow;
        return;
    }

    ITEM_set_cas(it, c->binary_header.request.cas);

    switch (c->cmd) {
        case PROTOCOL_BINARY_CMD_ADD:
            c->cmd = NREAD_ADD;
            break;
        case PROTOCOL_BINARY_CMD_SET:
            c->cmd = NREAD_SET;
            break;
        case PROTOCOL_BINARY_CMD_REPLACE:
            c->cmd = NREAD_REPLACE;
            break;
        default:
            assert(0);
    }

    if (ITEM_get_cas(it) != 0) {
        c->cmd = NREAD_CAS;
    }

    c->item = it;
#ifdef NEED_ALIGN
    if (it->it_flags & ITEM_CHUNKED) {
        c->ritem = ITEM_schunk(it);
    } else {
        c->ritem = ITEM_data(it);
    }
#else
    c->ritem = ITEM_data(it);
#endif
    c->rlbytes = vlen;
    conn_set_state(c, conn_nread);
    c->substate = bin_read_set_value;
}