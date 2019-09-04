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
struct TYPE_4__ {void* cbuf; int /*<<< orphan*/  buf; int /*<<< orphan*/ * c; } ;
typedef  TYPE_1__ crawler_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  LRU_CRAWLER_WRITEBUF ; 
 void* bipbuf_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lru_crawler_poll (TYPE_1__*) ; 

__attribute__((used)) static int lru_crawler_client_getbuf(crawler_client_t *c) {
    void *buf = NULL;
    if (c->c == NULL) return -1;
    /* not enough space. */
    while ((buf = bipbuf_request(c->buf, LRU_CRAWLER_WRITEBUF)) == NULL) {
        // TODO: max loops before closing.
        int ret = lru_crawler_poll(c);
        if (ret < 0) return ret;
    }

    c->cbuf = buf;
    return 0;
}