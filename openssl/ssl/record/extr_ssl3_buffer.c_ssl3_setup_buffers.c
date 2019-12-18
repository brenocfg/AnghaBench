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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ssl3_setup_read_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl3_setup_write_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int ssl3_setup_buffers(SSL *s)
{
    if (!ssl3_setup_read_buffer(s)) {
        /* SSLfatal() already called */
        return 0;
    }
    if (!ssl3_setup_write_buffer(s, 1, 0)) {
        /* SSLfatal() already called */
        return 0;
    }
    return 1;
}