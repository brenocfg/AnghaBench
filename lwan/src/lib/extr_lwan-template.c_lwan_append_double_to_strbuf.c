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
struct lwan_strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lwan_strbuf_append_printf (struct lwan_strbuf*,char*,double) ; 

void lwan_append_double_to_strbuf(struct lwan_strbuf *buf, void *ptr)
{
    lwan_strbuf_append_printf(buf, "%f", *(double *)ptr);
}