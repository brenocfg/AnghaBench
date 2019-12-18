#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int distance; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ QueryOperand ;

/* Variables and functions */
 int tsCompareString (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
compareQueryOperand(const void *a, const void *b, void *arg)
{
	char	   *operand = (char *) arg;
	QueryOperand *qa = (*(QueryOperand *const *) a);
	QueryOperand *qb = (*(QueryOperand *const *) b);

	return tsCompareString(operand + qa->distance, qa->length,
						   operand + qb->distance, qb->length,
						   false);
}