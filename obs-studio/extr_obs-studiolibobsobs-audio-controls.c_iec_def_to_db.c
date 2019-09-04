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
 float INFINITY ; 

__attribute__((used)) static float iec_def_to_db(const float def)
{
	if (def == 1.0f)
		return 0.0f;
	else if (def <= 0.0f)
		return -INFINITY;

	float db;

	if (def >= 0.75f)
		db = (def - 1.0f) / 0.25f * 9.0f;
	else if (def >= 0.5f)
		db = (def - 0.75f) / 0.25f * 11.0f - 9.0f;
	else if (def >= 0.3f)
		db = (def - 0.5f) / 0.2f * 10.0f - 20.0f;
	else if (def >= 0.15f)
		db = (def - 0.3f) / 0.15f * 10.0f - 30.0f;
	else if (def >= 0.075f)
		db = (def - 0.15f) / 0.075f * 10.0f - 40.0f;
	else if (def >= 0.025f)
		db = (def - 0.075f) / 0.05f * 10.0f - 50.0f;
	else if (def >= 0.001f)
		db = (def - 0.025f) / 0.025f * 90.0f - 60.0f;
	else
		db = -INFINITY;

	return db;
}