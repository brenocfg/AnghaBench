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
struct bluray_priv_s {int /*<<< orphan*/  bd; } ;
struct TYPE_4__ {struct bluray_priv_s* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  BD_EVENT ;

/* Variables and functions */
 scalar_t__ bd_get_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bd_read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  handle_event (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bluray_stream_fill_buffer(stream_t *s, void *buf, int len)
{
    struct bluray_priv_s *b = s->priv;
    BD_EVENT event;
    while (bd_get_event(b->bd, &event))
        handle_event(s, &event);
    return bd_read(b->bd, buf, len);
}