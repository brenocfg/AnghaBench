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
struct TYPE_4__ {char const* str; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ str; } ;

/* Variables and functions */
 scalar_t__ xmlrpc_base64 ; 

const char* XMLRPC_GetValueBase64(XMLRPC_VALUE value) {
    return ((value && value->type == xmlrpc_base64) ? value->str.str : 0);
}