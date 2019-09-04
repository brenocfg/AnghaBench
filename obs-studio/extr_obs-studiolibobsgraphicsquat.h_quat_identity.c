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
struct quat {float w; int /*<<< orphan*/  m; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_setzero_ps () ; 

__attribute__((used)) static inline void quat_identity(struct quat *q)
{
	q->m = _mm_setzero_ps();
	q->w = 1.0f;
}