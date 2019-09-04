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
struct idr {int /*<<< orphan*/  idr_next; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int idr_get_cursor(const struct idr *idr)
{
	return READ_ONCE(idr->idr_next);
}