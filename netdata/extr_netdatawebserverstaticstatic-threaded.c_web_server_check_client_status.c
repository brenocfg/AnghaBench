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
 scalar_t__ unlikely (int) ; 
 scalar_t__ web_client_check_dead (struct web_client*) ; 
 int /*<<< orphan*/  web_client_has_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_has_wait_send (struct web_client*) ; 

__attribute__((used)) static inline int web_server_check_client_status(struct web_client *w) {
    if(unlikely(web_client_check_dead(w) || (!web_client_has_wait_receive(w) && !web_client_has_wait_send(w))))
        return -1;

    return 0;
}