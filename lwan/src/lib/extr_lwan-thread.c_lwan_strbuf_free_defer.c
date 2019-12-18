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
 int /*<<< orphan*/  lwan_strbuf_free (struct lwan_strbuf*) ; 

__attribute__((used)) static void lwan_strbuf_free_defer(void *data)
{
    lwan_strbuf_free((struct lwan_strbuf *)data);
}