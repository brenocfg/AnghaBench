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
struct limiter_data {size_t envelope_buf_len; int /*<<< orphan*/  envelope_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  brealloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void resize_env_buffer(struct limiter_data *cd, size_t len)
{
	cd->envelope_buf_len = len;
	cd->envelope_buf = brealloc(cd->envelope_buf, len * sizeof(float));
}