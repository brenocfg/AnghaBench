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
typedef  int u32 ;
struct afs_volume {int /*<<< orphan*/  name; int /*<<< orphan*/  vid; } ;

/* Variables and functions */
#define  VOFFLINE 130 
#define  VRESTARTING 129 
#define  VSALVAGING 128 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void afs_busy(struct afs_volume *volume, u32 abort_code)
{
	const char *m;

	switch (abort_code) {
	case VOFFLINE:		m = "offline";		break;
	case VRESTARTING:	m = "restarting";	break;
	case VSALVAGING:	m = "being salvaged";	break;
	default:		m = "busy";		break;
	}

	pr_notice("kAFS: Volume %llu '%s' is %s\n", volume->vid, volume->name, m);
}