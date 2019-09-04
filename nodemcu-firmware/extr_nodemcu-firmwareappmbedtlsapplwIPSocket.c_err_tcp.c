#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_4__* tcp; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ lwIP_netconn ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_6__ {int state; int /*<<< orphan*/  nrtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CONN ; 
 int /*<<< orphan*/  ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_LOG (char*,char*,int,TYPE_4__*) ; 
#define  ESTABLISHED 129 
 int /*<<< orphan*/  NETCONN_STATE_ERROR ; 
#define  SYN_SENT 128 
 int /*<<< orphan*/  TCP_MAXRTX ; 
 int /*<<< orphan*/  TCP_SYNMAXRTX ; 
 int /*<<< orphan*/  find_socket (TYPE_1__*) ; 
 int /*<<< orphan*/  lwIP_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  lwIP_EVENT_PARSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void err_tcp(void *arg, err_t err)
{
    lwIP_netconn *conn = arg;
    lwIP_ASSERT(conn);
    conn->state = NETCONN_STATE_ERROR;
    ESP_LOG("%s %d %p\n",__FILE__, __LINE__, conn->tcp);
    switch (conn->tcp->state)
    {
        case SYN_SENT:
            if (conn->tcp->nrtx == TCP_SYNMAXRTX)
            {
                err = ERR_CONN;
            }
            break;
        case ESTABLISHED:
            if (conn->tcp->nrtx == TCP_MAXRTX)
            {
                err = ERR_TIMEOUT;
            }
            break;
        default:
            break;
    }

    lwIP_EVENT_PARSE(find_socket(conn), err);
    return;
}