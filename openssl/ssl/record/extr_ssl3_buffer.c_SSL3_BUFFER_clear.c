#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ left; scalar_t__ offset; } ;
typedef  TYPE_1__ SSL3_BUFFER ;

/* Variables and functions */

void SSL3_BUFFER_clear(SSL3_BUFFER *b)
{
    b->offset = 0;
    b->left = 0;
}