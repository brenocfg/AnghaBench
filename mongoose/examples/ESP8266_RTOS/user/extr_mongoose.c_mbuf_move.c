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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct mbuf*,struct mbuf*,int) ; 
 int /*<<< orphan*/  memset (struct mbuf*,int /*<<< orphan*/ ,int) ; 

void mbuf_move(struct mbuf *from, struct mbuf *to) {
  memcpy(to, from, sizeof(*to));
  memset(from, 0, sizeof(*from));
}