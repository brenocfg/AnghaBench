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

/* Variables and functions */
 float const INFINITY ; 
 float cbrtf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_to_mul (float const) ; 

__attribute__((used)) static float cubic_db_to_def(const float db)
{
	if (db == 0.0f)
		return 1.0f;
	else if (db == -INFINITY)
		return 0.0f;

	return cbrtf(db_to_mul(db));
}