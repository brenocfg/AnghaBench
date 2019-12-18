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
struct priv {int in_rate; int /*<<< orphan*/  avrctx; scalar_t__ out_rate; } ;
typedef  int int64_t ;

/* Variables and functions */
 double swr_get_delay (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static double get_delay(struct priv *p)
{
    int64_t base = p->in_rate * (int64_t)p->out_rate;
    return swr_get_delay(p->avrctx, base) / (double)base;
}