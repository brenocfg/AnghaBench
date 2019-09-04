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
struct limiter_data {struct limiter_data* envelope_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct limiter_data*) ; 

__attribute__((used)) static void limiter_destroy(void *data)
{
	struct limiter_data *cd = data;

	bfree(cd->envelope_buf);
	bfree(cd);
}