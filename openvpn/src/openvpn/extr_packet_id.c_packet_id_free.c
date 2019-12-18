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
struct TYPE_2__ {scalar_t__ seq_list; } ;
struct packet_id {TYPE_1__ rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct packet_id) ; 
 int /*<<< orphan*/  D_PID_DEBUG ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void
packet_id_free(struct packet_id *p)
{
    if (p)
    {
        dmsg(D_PID_DEBUG, "PID packet_id_free");
        if (p->rec.seq_list)
        {
            free(p->rec.seq_list);
        }
        CLEAR(*p);
    }
}