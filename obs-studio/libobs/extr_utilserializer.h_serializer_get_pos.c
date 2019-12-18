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
struct serializer {int (* get_pos ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
typedef  int int64_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int64_t serializer_get_pos(struct serializer *s)
{
	if (s && s->get_pos)
		return s->get_pos(s->data);
	return -1;
}