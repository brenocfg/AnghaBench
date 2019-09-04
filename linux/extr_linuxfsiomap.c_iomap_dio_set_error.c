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
struct iomap_dio {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void iomap_dio_set_error(struct iomap_dio *dio, int ret)
{
	cmpxchg(&dio->error, 0, ret);
}