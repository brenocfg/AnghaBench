#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* XMLRPC_VALUE ;
struct TYPE_4__ {scalar_t__ str; scalar_t__ len; } ;
struct TYPE_5__ {TYPE_1__ id; } ;

/* Variables and functions */

const char* XMLRPC_GetValueID(XMLRPC_VALUE value) {
    return (const char*)((value && value->id.len) ? value->id.str : 0);
}