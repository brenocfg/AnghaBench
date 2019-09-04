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
struct circlebuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct circlebuf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void circlebuf_init(struct circlebuf *cb)
{
	memset(cb, 0, sizeof(struct circlebuf));
}