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
struct TYPE_2__ {int /*<<< orphan*/  sockets; } ;

/* Variables and functions */
 int listen_sockets_setup (int /*<<< orphan*/ *) ; 
 TYPE_1__ statsd ; 

__attribute__((used)) static int statsd_listen_sockets_setup(void) {
    return listen_sockets_setup(&statsd.sockets);
}