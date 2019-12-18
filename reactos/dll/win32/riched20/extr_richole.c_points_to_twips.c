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
typedef  int FLOAT ;

/* Variables and functions */

__attribute__((used)) static inline FLOAT points_to_twips(FLOAT value)
{
    return value * 1440 / 72.0;
}