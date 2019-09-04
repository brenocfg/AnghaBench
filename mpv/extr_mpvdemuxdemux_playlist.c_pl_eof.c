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
struct pl_parser {TYPE_1__* s; scalar_t__ error; } ;
struct TYPE_2__ {scalar_t__ eof; } ;

/* Variables and functions */

__attribute__((used)) static bool pl_eof(struct pl_parser *p)
{
    return p->error || p->s->eof;
}