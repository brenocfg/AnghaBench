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
typedef  int /*<<< orphan*/  uint8_t ;
struct obs_qsv {size_t sei_size; int /*<<< orphan*/ * sei; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (size_t*) ; 

__attribute__((used)) static bool obs_qsv_sei(void *data, uint8_t **sei, size_t *size)
{
	struct obs_qsv *obsqsv = data;

	if (!obsqsv->context)
		return false;

	/* (Jim) Unused */
	UNUSED_PARAMETER(sei);
	UNUSED_PARAMETER(size);

	*sei = obsqsv->sei;
	*size = obsqsv->sei_size;
	return true;
}