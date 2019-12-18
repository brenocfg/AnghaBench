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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int mp_msg_level (struct mp_log*) ; 

__attribute__((used)) static inline bool mp_msg_test(struct mp_log *log, int lev)
{
    return lev <= mp_msg_level(log);
}