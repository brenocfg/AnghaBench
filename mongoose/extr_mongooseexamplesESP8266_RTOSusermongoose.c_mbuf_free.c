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
struct mbuf {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int /*<<< orphan*/ ) ; 

void mbuf_free(struct mbuf *mbuf) {
  if (mbuf->buf != NULL) {
    MBUF_FREE(mbuf->buf);
    mbuf_init(mbuf, 0);
  }
}