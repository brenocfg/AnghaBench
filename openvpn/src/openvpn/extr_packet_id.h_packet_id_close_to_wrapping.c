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
struct packet_id_send {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ PACKET_ID_WRAP_TRIGGER ; 

__attribute__((used)) static inline bool
packet_id_close_to_wrapping(const struct packet_id_send *p)
{
    return p->id >= PACKET_ID_WRAP_TRIGGER;
}