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
struct mbuf {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 size_t mbuf_insert (struct mbuf*,int /*<<< orphan*/ ,void const*,size_t) ; 

size_t mbuf_append(struct mbuf *a, const void *buf, size_t len) {
  return mbuf_insert(a, a->len, buf, len);
}