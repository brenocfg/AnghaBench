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
struct mbuf {size_t size; size_t len; char* buf; } ;

/* Variables and functions */
 scalar_t__ MBUF_REALLOC (char*,size_t) ; 

void mbuf_resize(struct mbuf *a, size_t new_size) {
  if (new_size > a->size || (new_size < a->size && new_size >= a->len)) {
    char *buf = (char *) MBUF_REALLOC(a->buf, new_size);
    /*
     * In case realloc fails, there's not much we can do, except keep things as
     * they are. Note that NULL is a valid return value from realloc when
     * size == 0, but that is covered too.
     */
    if (buf == NULL && new_size != 0) return;
    a->buf = buf;
    a->size = new_size;
  }
}