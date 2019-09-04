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
struct TYPE_2__ {int /*<<< orphan*/ * header_output; int /*<<< orphan*/ * header; int /*<<< orphan*/ * data; } ;
struct web_client {TYPE_1__ response; int /*<<< orphan*/  user_agent; } ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct web_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void web_client_zero(struct web_client *w) {
    // zero everything about it - but keep the buffers

    // remember the pointers to the buffers
    BUFFER *b1 = w->response.data;
    BUFFER *b2 = w->response.header;
    BUFFER *b3 = w->response.header_output;

    // empty the buffers
    buffer_flush(b1);
    buffer_flush(b2);
    buffer_flush(b3);

    freez(w->user_agent);

    // zero everything
    memset(w, 0, sizeof(struct web_client));

    // restore the pointers of the buffers
    w->response.data = b1;
    w->response.header = b2;
    w->response.header_output = b3;
}