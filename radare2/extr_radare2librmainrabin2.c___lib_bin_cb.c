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
struct r_bin_plugin_t {int dummy; } ;
typedef  int /*<<< orphan*/  RLibPlugin ;

/* Variables and functions */
 int /*<<< orphan*/  bin ; 
 int /*<<< orphan*/  r_bin_add (int /*<<< orphan*/ ,struct r_bin_plugin_t*) ; 

__attribute__((used)) static int __lib_bin_cb(RLibPlugin *pl, void *user, void *data) {
	struct r_bin_plugin_t *hand = (struct r_bin_plugin_t *)data;
	//printf(" * Added (dis)assembly plugin\n");
	r_bin_add (bin, hand);
	return true;
}