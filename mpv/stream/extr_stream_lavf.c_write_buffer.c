#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_7__ {scalar_t__ error; } ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_flush (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_write (TYPE_2__*,void*,int) ; 

__attribute__((used)) static int write_buffer(stream_t *s, void *buffer, int len)
{
    AVIOContext *avio = s->priv;
    avio_write(avio, buffer, len);
    avio_flush(avio);
    if (avio->error)
        return -1;
    return len;
}