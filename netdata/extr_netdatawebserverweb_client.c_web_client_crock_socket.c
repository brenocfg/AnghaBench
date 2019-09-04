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
struct web_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int web_client_crock_socket(struct web_client *w) {
#ifdef TCP_CORK
    if(likely(web_client_is_corkable(w) && !w->tcp_cork && w->ofd != -1)) {
        w->tcp_cork = 1;
        if(unlikely(setsockopt(w->ofd, IPPROTO_TCP, TCP_CORK, (char *) &w->tcp_cork, sizeof(int)) != 0)) {
            error("%llu: failed to enable TCP_CORK on socket.", w->id);

            w->tcp_cork = 0;
            return -1;
        }
    }
#else
    (void)w;
#endif /* TCP_CORK */

    return 0;
}