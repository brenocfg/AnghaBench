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
struct mp_log {int /*<<< orphan*/  partial; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_log(void *ptr)
{
    struct mp_log *log = ptr;
    // This is not managed via talloc itself, because mp_msg calls must be
    // thread-safe, while talloc is not thread-safe.
    talloc_free(log->partial);
}