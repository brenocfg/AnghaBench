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
 int INT_TO_STR_BUFFER_SIZE ; 
 char* int_to_string (int,char*,size_t*) ; 
 int /*<<< orphan*/  lwan_strbuf_append_str (struct lwan_strbuf*,char*,size_t) ; 

void lwan_append_int_to_strbuf(struct lwan_strbuf *buf, void *ptr)
{
    char convertbuf[INT_TO_STR_BUFFER_SIZE];
    size_t len;
    char *converted;

    converted = int_to_string(*(int *)ptr, convertbuf, &len);
    lwan_strbuf_append_str(buf, converted, len);
}