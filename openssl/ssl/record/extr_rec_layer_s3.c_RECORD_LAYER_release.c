#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ numwpipes; int /*<<< orphan*/  rrec; int /*<<< orphan*/  s; int /*<<< orphan*/  rbuf; } ;
typedef  TYPE_1__ RECORD_LAYER ;

/* Variables and functions */
 scalar_t__ SSL3_BUFFER_is_initialised (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_RECORD_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_MAX_PIPELINES ; 
 int /*<<< orphan*/  ssl3_release_read_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_release_write_buffer (int /*<<< orphan*/ ) ; 

void RECORD_LAYER_release(RECORD_LAYER *rl)
{
    if (SSL3_BUFFER_is_initialised(&rl->rbuf))
        ssl3_release_read_buffer(rl->s);
    if (rl->numwpipes > 0)
        ssl3_release_write_buffer(rl->s);
    SSL3_RECORD_release(rl->rrec, SSL_MAX_PIPELINES);
}