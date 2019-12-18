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
struct pbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

__attribute__((used)) static void
pbuf_free_int(void *p)
{
  struct pbuf *q = (struct pbuf *)p;
  pbuf_free(q);
}