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
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  lwan_strbuf_append_char (struct lwan_strbuf*,int) ; 

__attribute__((used)) static void write_num(struct lwan_strbuf *buf, int16_t num)
{
    lwan_strbuf_append_char(buf, num & 0xff);
    lwan_strbuf_append_char(buf, num >> 8);
}