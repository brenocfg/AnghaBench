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
struct packet_id_persist {int /*<<< orphan*/  filename; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int D_PID_PERSIST ; 
 int M_ERRNO ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ packet_id_persist_enabled (struct packet_id_persist*) ; 
 int /*<<< orphan*/  packet_id_persist_init (struct packet_id_persist*) ; 

void
packet_id_persist_close(struct packet_id_persist *p)
{
    if (packet_id_persist_enabled(p))
    {
        if (close(p->fd))
        {
            msg(D_PID_PERSIST | M_ERRNO, "Close error on --replay-persist file %s", p->filename);
        }
        packet_id_persist_init(p);
    }
}