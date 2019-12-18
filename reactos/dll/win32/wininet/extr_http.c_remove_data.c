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
struct TYPE_3__ {int read_size; scalar_t__ read_pos; } ;
typedef  TYPE_1__ http_request_t ;

/* Variables and functions */

__attribute__((used)) static void remove_data( http_request_t *req, int count )
{
    if (!(req->read_size -= count)) req->read_pos = 0;
    else req->read_pos += count;
}