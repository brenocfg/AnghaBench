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
struct TYPE_4__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ lwIP_sock ;

/* Variables and functions */
 int NUM_SOCKETS ; 
 TYPE_1__* sockets ; 

__attribute__((used)) static lwIP_sock *get_socket(int s)
{
    lwIP_sock *sock = NULL;

    if ((s < 0) || (s >= NUM_SOCKETS))
    {
        return NULL;
    }

    sock = &sockets[s];

    if (!sock->conn)
    {
        return NULL;
    }

    return sock;
}