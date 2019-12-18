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
struct hdspm {scalar_t__ io_type; } ;

/* Variables and functions */
 scalar_t__ AIO ; 
 scalar_t__ RayDAT ; 

__attribute__((used)) static bool hdspm_is_raydat_or_aio(struct hdspm *hdspm)
{
	return ((AIO == hdspm->io_type) || (RayDAT == hdspm->io_type));
}