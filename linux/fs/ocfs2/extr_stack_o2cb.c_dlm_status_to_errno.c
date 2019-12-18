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
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int* status_map ; 

__attribute__((used)) static int dlm_status_to_errno(enum dlm_status status)
{
	BUG_ON(status < 0 || status >= ARRAY_SIZE(status_map));

	return status_map[status];
}