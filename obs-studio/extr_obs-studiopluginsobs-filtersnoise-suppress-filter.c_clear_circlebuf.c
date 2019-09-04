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
struct circlebuf {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_pop_front (struct circlebuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_circlebuf(struct circlebuf *buf)
{
	circlebuf_pop_front(buf, NULL, buf->size);
}