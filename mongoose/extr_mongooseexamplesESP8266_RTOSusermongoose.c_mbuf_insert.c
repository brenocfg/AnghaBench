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
struct mbuf {size_t len; size_t size; char* buf; } ;

/* Variables and functions */
 scalar_t__ MBUF_REALLOC (char*,size_t) ; 
 size_t MBUF_SIZE_MAX_HEADROOM ; 
 size_t MBUF_SIZE_MULTIPLIER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 

size_t mbuf_insert(struct mbuf *a, size_t off, const void *buf, size_t len) {
  char *p = NULL;

  assert(a != NULL);
  assert(a->len <= a->size);
  assert(off <= a->len);

  /* check overflow */
  if (~(size_t) 0 - (size_t) a->buf < len) return 0;

  if (a->len + len <= a->size) {
    memmove(a->buf + off + len, a->buf + off, a->len - off);
    if (buf != NULL) {
      memcpy(a->buf + off, buf, len);
    }
    a->len += len;
  } else {
    size_t min_size = (a->len + len);
    size_t new_size = (size_t)(min_size * MBUF_SIZE_MULTIPLIER);
    if (new_size - min_size > MBUF_SIZE_MAX_HEADROOM) {
      new_size = min_size + MBUF_SIZE_MAX_HEADROOM;
    }
    p = (char *) MBUF_REALLOC(a->buf, new_size);
    if (p == NULL && new_size != min_size) {
      new_size = min_size;
      p = (char *) MBUF_REALLOC(a->buf, new_size);
    }
    if (p != NULL) {
      a->buf = p;
      if (off != a->len) {
        memmove(a->buf + off + len, a->buf + off, a->len - off);
      }
      if (buf != NULL) memcpy(a->buf + off, buf, len);
      a->len += len;
      a->size = new_size;
    } else {
      len = 0;
    }
  }

  return len;
}