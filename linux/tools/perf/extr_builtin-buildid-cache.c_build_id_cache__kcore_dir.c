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
 int fetch_current_timestamp (char*,size_t) ; 

__attribute__((used)) static int build_id_cache__kcore_dir(char *dir, size_t sz)
{
	return fetch_current_timestamp(dir, sz);
}