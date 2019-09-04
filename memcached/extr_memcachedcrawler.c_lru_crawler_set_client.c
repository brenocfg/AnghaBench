#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sfd; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * c; } ;
struct TYPE_4__ {TYPE_2__ c; } ;
typedef  TYPE_1__ crawler_module_t ;
typedef  TYPE_2__ crawler_client_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bipbuf_new (int) ; 

__attribute__((used)) static int lru_crawler_set_client(crawler_module_t *cm, void *c, const int sfd) {
    crawler_client_t *crawlc = &cm->c;
    if (crawlc->c != NULL) {
        return -1;
    }
    crawlc->c = c;
    crawlc->sfd = sfd;

    crawlc->buf = bipbuf_new(1024 * 128);
    if (crawlc->buf == NULL) {
        return -2;
    }
    return 0;
}