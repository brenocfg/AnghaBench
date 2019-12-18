#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {short cmd_slot; scalar_t__ reply_type; TYPE_7__* cmd_sock; TYPE_1__* flags; } ;
typedef  TYPE_2__ redisCluster ;
struct TYPE_11__ {scalar_t__ mode; } ;
struct TYPE_9__ {scalar_t__ mode; } ;
typedef  scalar_t__ REDIS_REPLY_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MULTI ; 
 TYPE_7__* SLOT_SOCK (TYPE_2__*,short) ; 
 scalar_t__ TYPE_EOF ; 
 scalar_t__ cluster_check_response (TYPE_2__*,scalar_t__*) ; 
 int cluster_send_multi (TYPE_2__*,short) ; 
 int cluster_sock_write (TYPE_2__*,char*,int,int) ; 

int cluster_send_slot(redisCluster *c, short slot, char *cmd,
                             int cmd_len, REDIS_REPLY_TYPE rtype)
{
    /* Point our cluster to this slot and it's socket */
    c->cmd_slot = slot;
    c->cmd_sock = SLOT_SOCK(c, slot);

    /* Enable multi mode on this slot if we've been directed to but haven't
     * send it to this node yet */
    if (c->flags->mode == MULTI && c->cmd_sock->mode != MULTI) {
        if (cluster_send_multi(c, slot) == -1) {
            CLUSTER_THROW_EXCEPTION("Unable to enter MULTI mode on requested slot", 0);
            return -1;
        }
    }

    /* Try the slot */
    if (cluster_sock_write(c, cmd, cmd_len, 1) == -1) {
        return -1;
    }

    /* Check our response */
    if (cluster_check_response(c, &c->reply_type) != 0 ||
       (rtype != TYPE_EOF && rtype != c->reply_type)) return -1;

    /* Success */
    return 0;
}