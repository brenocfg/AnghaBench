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
struct dirent {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vhci_hcd_filter(const struct dirent *dirent)
{
	return !strncmp(dirent->d_name, "vhci_hcd.", 9);
}