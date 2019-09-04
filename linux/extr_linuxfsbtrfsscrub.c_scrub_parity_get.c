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
struct scrub_parity {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scrub_parity_get(struct scrub_parity *sparity)
{
	refcount_inc(&sparity->refs);
}