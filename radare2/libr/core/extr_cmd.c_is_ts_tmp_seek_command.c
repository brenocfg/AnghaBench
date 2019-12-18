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
typedef  int /*<<< orphan*/  TSNode ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ts_node_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_ts_tmp_seek_command(TSNode node) {
	return strcmp (ts_node_type (node), "tmp_seek_command") == 0;
}