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
struct raw3270_request {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
raw3270_request_final(struct raw3270_request *rq)
{
	return list_empty(&rq->list);
}