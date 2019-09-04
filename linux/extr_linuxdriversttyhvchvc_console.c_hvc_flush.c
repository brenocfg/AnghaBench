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
struct hvc_struct {int /*<<< orphan*/  vtermno; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int __hvc_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hvc_flush(struct hvc_struct *hp)
{
	return __hvc_flush(hp->ops, hp->vtermno, true);
}