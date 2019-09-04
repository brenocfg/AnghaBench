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
struct vo_internal {int terminate; } ;
struct vo {struct vo_internal* in; } ;

/* Variables and functions */

__attribute__((used)) static void terminate_vo(void *p)
{
    struct vo *vo = p;
    struct vo_internal *in = vo->in;
    in->terminate = true;
}